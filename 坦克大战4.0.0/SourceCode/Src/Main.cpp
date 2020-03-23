//-----------------------------------------------------------------------------
// ̹�˴�ս
//-----------------------------------------------------------------------------
#include "CommonAPI.h"
#include "stdio.h"
#include "List.h"


// ȫ�ֱ����������������ʼ��


Weapon*		g_pMyTank		=	NULL;	// �ҷ�̹��
bool		g_bStart		=	false;  // ����һ����Ϸ��ʼ�����
int			g_iScore		=	0;		// һ����Ϸ�÷�
float		g_fGameTime		=	0.f;    // һ����Ϸ��ʣ��ʱ��
int			g_iWallCount	=	0;		// ��¼ǽ������
int			g_iMap[11][13];				// ��ͼ����
int			g_iNum			=	0;		// ��¼�ҷ��ӵ����ҷ�̹�ˡ��з�̹�˵�����
float		g_fCreateTime	=	0.f;	// ÿ��������̹�˵�ʣ��ʱ��

const float	FIRE_TIME		=  2.f;		// �з�̹�˷����ڵ���ʱ����
const float CREATE_TANK_TIME = 5.f;		// ÿ��������̹�˵�ʱ����
const float	GAME_TIME		=	60.f;	// һ����Ϸ��ʱ��
const float	TANK_SPEED		 = 10.f;     // �з�̹���ٶ�
const float BULLET_SPEED	 = 20.f;		// �ӵ��ٶ�
const float ROTATE_TIME		 = 2.f;     // �з�̹�˵�ת�����ʱ��

const float	WORLD_LEFT	     = -26.f;	// ��Ϸ�����߽���ֵ
const float	WORLD_TOP	     = -22.f;	// ��Ϸ�����߽���ֵ
const float	WORLD_RIGHT	     = 26.f;	// ��Ϸ�����߽���ֵ
const float	WORLD_BOTTOM     = 22.f;	// ��Ϸ�����߽���ֵ


// ��������
void	MoveMyTank(int, bool);
void	LoadMap();
void	OnFire(char*, int);
void	CreateEnemyTanks();
void	MoveEnemyTank(const char*);
bool	IsDead(const char*);

// ��ײ����
void	OnMyTankColOther(const char*, const char*);
void	OnBulletColOther(const char*, const char*);
void	OnWallColOther(const char*, const char*);
void	OnTankColOther(const char*, const char*);
void	OnGoalColOther();

///////////////////////////////////////////////////////////////////////////////////////////
//
// ���������
//
//////////////////////////////////////////////////////////////////////////////////////////
int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine,
                   int       nCmdShow)
{
    // ��ʼ����Ϸ����
    if( !dInitGameEngine( hInstance, lpCmdLine ) )
        return 0;

    // ---------------- ��Ϸ��ʼ������ -----------

    dSetWindowTitle("̹�˴�ս");  // ������Ϸ���ڱ���

    // �������̹��1
    g_pMyTank = (Weapon*)malloc(sizeof(Weapon));
    strcpy(g_pMyTank->szName, "player");
    g_pMyTank->iHp = 1;
    dSetSpriteWorldLimit(g_pMyTank->szName, WORLD_LIMIT_NULL, WORLD_LEFT, WORLD_TOP, WORLD_RIGHT, WORLD_BOTTOM); // �����ҷ�̹������߽�
    dSetSpriteCollisionSend(g_pMyTank->szName, true);

    float fPosX0, fPosY0;  // ��ʼ����ʱ��̹�˵�����
    fPosX0 = dGetSpritePositionX(g_pMyTank->szName);
    fPosY0 = dGetSpritePositionY(g_pMyTank->szName);
    bool	bLoad	= true;		// �Ƿ������ͼ


    // -------------------------------------------

    // ��Ϸ��ѭ��
    while( dEngineMainLoop() ) // ������Ϸ���棬ˢ����Ϸ��Ļ��������ر�ʱ������false
    {
        // ---------- ��Ϸ��ѭ������ -------------

        // ��ȡ���ε���֮���ʱ�����ݸ���Ϸ�߼�����
        float	fTimeDelta	=	dGetTimeDelta();


        if(g_bStart)
        {
            if(bLoad)  // һ����Ϸֻ��Ҫ����һ�ε�ͼ����
            {
                // �����ͼ
                LoadMap();
                bLoad = false;
                //CreateEnemyTanks();
            }

            g_fGameTime -= fTimeDelta;
            if(g_fGameTime > 0.f) // һ����Ϸ������
            {
                dSetTextValue("time", (int)g_fGameTime);
                dSetTextValue("score", g_iScore);

                // ʱ�䵽��������һ���з�̹��
                g_fCreateTime -= fTimeDelta;
                if(g_fCreateTime < 0.f)
                {
                    //tNum++;
                    g_fCreateTime = CREATE_TANK_TIME;
                    CreateEnemyTanks();
                }


                // ����ڵ�ָ��
                Weapon* pNode	= g_pHead;
                int num = GetListSize();  // ��ǰ����Ľڵ�����
                // ������ǰ����Ѱ�ҵз�̹�˽ڵ�
                for(int i=0; i<num; i++)
                {
                    if(pNode->iType == ENEMYTANK)  // �з�̹��
                    {
                        // ���з�̹�˵�ת����ʱ��
                        pNode->fRotateTime -= fTimeDelta;
                        if(pNode->fRotateTime < 0.f)
                        {
                            pNode->fRotateTime = ROTATE_TIME;
                            MoveEnemyTank(pNode->szName);
                        }
                        pNode->fFireTime -= fTimeDelta;
                        if(pNode->fFireTime < 0.f)
                        {
                            pNode->fFireTime = FIRE_TIME;
                            OnFire(pNode->szName, ENEMYBULLET);
                        }

                    }
                    pNode = pNode->pNext;
                }

            }
            else // һ����Ϸ����
            {
                g_bStart = false;
            }
        }
        else
        {
            dSetSpriteVisible("kaishi", true);
            dSetSpriteLinearVelocity(g_pMyTank->szName, 0.f, 0.f);
            dSetSpritePosition(g_pMyTank->szName, fPosX0, fPosY0);
            dSetSpriteRotation(g_pMyTank->szName, 0);
            dSetTextValue("time", 0);

            // ɾ����ͼ
            char szName[128];
            for(int i=0; i<g_iWallCount; i++)
            {
                sprintf(szName, "wall%d", i);
                dDeleteSprite(szName);
            }
            g_iWallCount = 0;
            bLoad = true;
            // ɾ�����ྫ��
            DeleteList();

            // ����ָ�Ӳ����ɼ�
            dSetSpriteVisible("goal", false);
        }


        // ----------------------------------------

    };

    // �ر���Ϸ����
    dShutdownGameEngine();
    return 0;
}



//==========================================================================
//
// ���沶׽����ƶ���Ϣ�󣬽����õ�������
// fMouseX���������λ�õ�X����
// fMouseY���������λ�õ�Y����
void dOnMouseMove( const float fMouseX, const float fMouseY )
{
    // �ڴ������껬������Ӧ����

}
//==========================================================================
//
// ���沶׽�������Ϣ�󣬽����õ�������
// iMouseType��0 - ��������1 - ����м��� 2 - ����Ҽ�
// fMouseX���������λ�õ�X����
// fMouseY���������λ�õ�Y����
void dOnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
    // �ڴ�������������Ӧ����

}
//==========================================================================
//
void dOnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{
    // �����ڴ������Ϸ��Ҫ����Ӧ����

}
// ���沶׽���̰�����Ϣ�󣬽����õ�������
// iKey�����µ�ĳ������
// iAltPress iShiftPress iCtrlPress �ֱ�Ϊ�ж�Shift��Alt��Ctrl��ǰ�Ƿ�Ҳ���ڰ���״̬����������ж�Ctrl+E��ϼ�
void dOnKeyDown( const int iKey, const int iAltPress, const int iShiftPress, const int iCtrlPress )
{
    // �ڴ���Ӽ��̰��µ���Ӧ����
    if(g_bStart)  // һ����Ϸ������
    {
        if(iKey == KEY_W || iKey == KEY_A || iKey == KEY_S || iKey == KEY_D )
        {

            MoveMyTank(iKey, true);
        }
        // ����J�����ҷ�̹�˷����ӵ�
        if(iKey == KEY_J)
            OnFire(g_pMyTank->szName, MYBULLET);
    }

    if(iKey == KEY_SPACE && g_bStart == false) // ��Ϸδ��ʼ�����¿ո��
    {
        g_bStart = true;
        g_fGameTime = GAME_TIME;
        dSetSpriteVisible("kaishi", false);
        dSetTextValue("time", (int)g_fGameTime);
        // ���ҷ�̹�˷��ڵ�11�е�5��
        dSetSpritePosition(g_pMyTank->szName, -24 + 4*4, -20 + 4*10);

        g_fCreateTime = CREATE_TANK_TIME;

        g_iScore = 0;
        dSetTextValue("score", g_iScore);
    }
}
//==========================================================================
//
// ���沶׽���̵�����Ϣ�󣬽����õ�������
// iKey�������ĳ������
void dOnKeyUp( const int iKey )
{
    // �ڴ�����μ��̵������Ӧ����
    if(g_bStart)
    {
        if(iKey == KEY_W || iKey == KEY_A || iKey == KEY_S || iKey == KEY_D )
        {
            MoveMyTank(iKey, false);
        }
    }
}

//===========================================================================
//
// ���沶׽�������뾫����ײ֮�󣬵��ô˺���
// szSrcName�������뾫����ײ�е�һ��
// szTarName�������뾫����ײ�е���һ��
void dOnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
    // �ڴ���Ӿ����뾫����ײ����Ӧ����
    // ������ײһ��
    if(strcmp(szSrcName, g_pMyTank->szName) == 0)  // �ҷ�̹��
        OnMyTankColOther(szSrcName, szTarName);

    if(strstr(szSrcName, "bullet") != NULL)           // �ӵ�
        OnBulletColOther(szSrcName, szTarName);

    if(strstr(szSrcName, "tank") != NULL)			  // �з�̹��
        OnTankColOther(szSrcName, szTarName);


    // ������ײһ��
    if(strstr(szTarName, "wall") != NULL)
        OnWallColOther(szTarName, szSrcName);

    if(strstr(szTarName, "bullet") != NULL)           // �ӵ�
        OnBulletColOther(szTarName, szSrcName);

    if(strstr(szTarName, "tank") != NULL)			  // �з�̹��
        OnTankColOther(szTarName, szSrcName);

    if(strcmp(szTarName, "goal") == 0)				// ���ָ�Ӳ�
        OnGoalColOther();

    Weapon* p0 = FindNode(szSrcName);
    Weapon* p1 = FindNode(szTarName);
    if(p1 != NULL && IsDead(szTarName))
    {
        dDeleteSprite(szTarName);
        DeleteNode(szTarName);
    }
    if(p0 != NULL && IsDead(szSrcName) && strstr(szSrcName, "bullet") != NULL)
    {
        dDeleteSprite(szSrcName);
        DeleteNode(szSrcName);
    }
}

//===========================================================================
//
// ���沶׽������������߽���ײ֮�󣬵��ô˺���.
// szName : ������߽���ײ�ľ��������
// iColSide : 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
void dOnSpriteColWorldLimit( const char *szName, const int iColSide )
{
    // �ڴ���Ӿ���������߽���ײ����Ӧ����
    if(strcmp(szName, g_pMyTank->szName)==0)  // ���̹��
    {
        dSetSpriteLinearVelocity(g_pMyTank->szName, 0.f, 0.f);
    }
    if(strstr(szName, "bullet") != NULL)   // �ӵ�
    {
        // ɾ������
        dDeleteSprite(szName);
        // ɾ����Ӧ����ڵ�
        DeleteNode(szName);
    }
    if(strstr(szName, "tank") != NULL)   // �з�̹��
    {
        float fSpeedX = 0.f, fSpeedY = 0.f;
        int	  iDir = 0;

        // ��ͷ
        switch(iColSide)
        {
        case 0:  // ������ߣ���ͷ����
            fSpeedX = TANK_SPEED;
            iDir = RIGHT;
            break;
        case 1:  // �����ұߣ���ͷ����
            fSpeedX = -TANK_SPEED;
            iDir =	LEFT;
            break;
        case 2:  // �����ϱߣ���ͷ����
            fSpeedY = TANK_SPEED;
            iDir = DOWN;
            break;
        case 3:  // �����±ߣ���ͷ����
            fSpeedY = -TANK_SPEED;
            iDir = UP;
            break;
        }
        dSetSpriteLinearVelocity(szName, fSpeedX, fSpeedY);
        dSetSpriteRotation(szName, iDir*90);

    }
}

// �ҷ�̹���˶�
void  MoveMyTank(int iKey, bool bPress)
{
    if(bPress)  // ���¼���
    {
        switch (iKey)
        {
        case KEY_W:
            g_pMyTank->iDir = UP;
            g_pMyTank->fSpeedX = 0.f;
            g_pMyTank->fSpeedY = -TANK_SPEED;
            break;
        case KEY_D:
            g_pMyTank->iDir = RIGHT;
            g_pMyTank->fSpeedX = TANK_SPEED;
            g_pMyTank->fSpeedY = 0.f;
            break;
        case KEY_S:
            g_pMyTank->iDir = DOWN;
            g_pMyTank->fSpeedX = 0.f;
            g_pMyTank->fSpeedY = TANK_SPEED;
            break;
        case KEY_A:
            g_pMyTank->iDir = LEFT;
            g_pMyTank->fSpeedX = -TANK_SPEED;
            g_pMyTank->fSpeedY = 0.f;
            break;
        }
    }
    else    // �ɿ�����
    {
        switch (iKey)
        {
        case KEY_W:
            g_pMyTank->fSpeedY = 0.f;
            break;
        case KEY_D:
            g_pMyTank->fSpeedX = 0.f;
            break;
        case KEY_S:
            g_pMyTank->fSpeedY = 0.f;
            break;
        case KEY_A:
            g_pMyTank->fSpeedX = 0.f;
            break;
        }
    }

    dSetSpriteRotation(g_pMyTank->szName, g_pMyTank->iDir * 90);
    dSetSpriteLinearVelocity(g_pMyTank->szName, g_pMyTank->fSpeedX, g_pMyTank->fSpeedY);

}

// �з�̹���˶�
void	MoveEnemyTank(const char* szName)
{
    int iDir = dGetSpriteRotation(szName) / 90;
    float	fSpeedX = 0, fSpeedY = 0;

    switch(iDir)
    {
    case 0:
        fSpeedX = TANK_SPEED;
        fSpeedY = 0;
        break;
    case 1:
        fSpeedX = 0;
        fSpeedY = TANK_SPEED;
        break;
    case 2:
        fSpeedX = -TANK_SPEED;
        fSpeedY = 0;
        break;
    case 3:
        fSpeedX = 0;
        fSpeedY = -TANK_SPEED;
    }
    iDir += 1;
    dSetSpriteLinearVelocity(szName, fSpeedX, fSpeedY);
    dSetSpriteRotation(szName, iDir*90);

}

// �����ͼ
void  LoadMap()
{
    // ��ͼ���� һ��11��13�еĵ�ͼ������1����ǽ
    int iMap[11][13]=
    {
        {0,2,0,0,0,0,0,0,0,0,0,2,0},
		{0,1,0,0,0,1,0,1,0,0,0,1,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1},
		{2,2,4,4,4,2,4,2,4,4,4,2,2},
		{4,1,4,1,1,3,3,3,1,1,4,0,0},
		{4,1,4,4,1,1,3,1,4,1,4,1,1},
		{1,1,1,1,0,0,3,1,1,1,1,4,1},
		{3,3,3,1,0,0,3,2,0,0,3,3,3},
		{0,0,3,2,2,2,3,2,2,2,3,0,0},
		{3,3,3,1,0,4,1,4,0,0,3,3,3},
		{1,1,1,1,0,1,0,1,0,0,0,1,0},
    };
    // ��ֵ��g_iMap
    int i,j;
    for(i=0; i<11; i++)
    {
        for(j=0; j<13; j++)
        {
            g_iMap[i][j] = iMap[i][j];
        }
    }

    // ���ص�ͼ
    // iMap[0][0] λ�ڵ�ͼ�ϵ�-24��-20��λ��

    char szName[128];

    float x,y;
    for(i=0; i<11; i++)
    {
        for(j=0; j<13; j++)
        {
            if(g_iMap[i][j]==1)
            {
                sprintf(szName, "wall%d", g_iWallCount++);
                dCloneSprite("wall",szName);
                // ��wall��Ϊ������ײ
                dSetSpriteCollisionReceive(szName, true);

                x = -24+4*j;
                y = -20+4*i;
                dSetSpritePosition(szName,x,y);
            }
            if(g_iMap[i][j]==2)
            {
                sprintf(szName, "grass%d", g_iWallCount++);
                dCloneSprite("grass",szName);
                // ��wall��Ϊ������ײ
                dSetSpriteCollisionReceive(szName, false);

                x = -24+4*j;
                y = -20+4*i;
                dSetSpritePosition(szName,x,y);
            }
            if(g_iMap[i][j]==3)
            {
                sprintf(szName, "sea%d", g_iWallCount++);
                dCloneSprite("sea",szName);
                // ��wall��Ϊ������ײ
                dSetSpriteCollisionReceive(szName, true);

                x = -24+4*j;
                y = -20+4*i;
                dSetSpritePosition(szName,x,y);
            }
            else if(g_iMap[i][j]==4)
            {
                sprintf(szName, "stock%d", g_iWallCount++);
                dCloneSprite("stock",szName);
                // ��wall��Ϊ������ײ
                dSetSpriteCollisionReceive(szName, true);

                x = -24+4*j;
                y = -20+4*i;
                dSetSpritePosition(szName,x,y);
            }
        }
    }

    // ָ�Ӳ������ڵ�11�е�7��
    dSetSpritePosition("goal", -0.f, 20.f);
    dSetSpriteVisible("goal", true);
    dSetSpriteCollisionReceive("goal", true);
}

// �ҷ�̹��������������ײ
void	OnMyTankColOther(const char* szTankName, const char* szOtherName)
{

    if(strstr(szOtherName, "wall") != NULL)
        dSetSpriteLinearVelocity(g_pMyTank->szName, 0, 0);
    if(strstr(szOtherName, "stock") != NULL)
        dSetSpriteLinearVelocity(g_pMyTank->szName, 0, 0);
        if(strstr(szOtherName, "sea") != NULL)
        dSetSpriteLinearVelocity(g_pMyTank->szName, 0, 0);
    if(strstr(szOtherName, "tank") != NULL)
        g_bStart = false;
    if(strstr(szOtherName, "bullet") != NULL)
        g_bStart = false;

}

// �ӵ�������������ײ
void	OnBulletColOther(const char* szBulletName, const char* szOtherName)
{
    Weapon * pBullet = FindNode(szBulletName);  // ���������ҳ���Ӧ���ӵ��ڵ�

    if(pBullet != NULL)
    {
        pBullet->iHp = 0;
    }

}

// ǽ������������ײ
void	OnWallColOther(const char* szWallName, const char* szOtherName)
{
    // ������ϵ����ӵ���ǽ��ɾ��
    if(strstr(szOtherName, "bullet") != NULL)
        dDeleteSprite(szWallName);

}

// �з�̹��������������ײ
void	OnTankColOther(const char* szTankName, const char* szOtherName)
{
    // ������ϵ���ǽ���з�̹��ͣ����
    if(strstr(szOtherName, "wall") != NULL)
    {
        dSetSpriteLinearVelocity(szTankName, 0.f, 0.f);
    }
    if(strstr(szOtherName, "sea") != NULL)
        dSetSpriteLinearVelocity(szTankName, 0.f, 0.f);
    if(strstr(szOtherName, "stock") != NULL)
        dSetSpriteLinearVelocity(szTankName, 0.f, 0.f);

    // ��������ҷ�̹�ˣ���Ϸ����
    if(strcmp(szOtherName, "player") == 0)
        g_bStart = false;

    // ������ϵ�������ӵ����з�̹�˱��ݻ٣���ҵ�һ��
    if(strstr(szOtherName, "bullet") != NULL)
    {
        Weapon* bullet = FindNode(szOtherName);
        Weapon* enemyTank = FindNode(szTankName);
        if(bullet != NULL && enemyTank != NULL && bullet->iType == MYBULLET)
        {
            enemyTank->iHp = 0;
            g_iScore++;
        }
    }

    // �������Ҳ�ǵз�̹�ˣ��з�̹��ͣ����
    if(strstr(szOtherName, "tank") != NULL)
    {
        float fSpeedX0 = dGetSpriteLinearVelocityX(szTankName);
        float fSpeedY0 = dGetSpriteLinearVelocityY(szTankName);
        // �����̹��ԭ�����ٶȣ���ͷǰ��

        if(fSpeedX0 > 0.0001)
        {
            dSetSpriteLinearVelocity(szTankName, -TANK_SPEED, 0);
            dSetSpriteRotation(szTankName, 270);
        }
        else
        {
            dSetSpriteLinearVelocity(szTankName, TANK_SPEED, 0);
            dSetSpriteRotation(szTankName, 90);
        }


        if(fSpeedY0 > 0.0001)
        {
            dSetSpriteLinearVelocity(szTankName, 0, -TANK_SPEED);
            dSetSpriteRotation(szTankName, 0);
        }
        else
        {
            dSetSpriteLinearVelocity(szTankName, 0, TANK_SPEED);
            dSetSpriteRotation(szTankName, 180);
        }

    }
}


// ���ָ����������������ײ
void	OnGoalColOther()
{
    g_bStart = false;
}


// �ж�ĳ�������Ƿ�����
bool IsDead(const char* szName)
{
    Weapon* pSprite = FindNode(szName);

    if(pSprite != NULL && pSprite->iHp == 0)
        return true;

    return false;
}

// ̹�˿���
// szName - ̹�˵�����
// iType - �ӵ�����
void OnFire(char* szName, int iType)
{
    char szBullet[128];
    float fPosX, fPosY;
    int iDir;
    float fSpeedX,fSpeedY;

    //���̹�˵ĳ���
    iDir = dGetSpriteRotation(szName)/90;
    sprintf(szBullet, "bullet%d",g_iNum++);
    dCloneSprite("bullet",szBullet);
    dSetSpriteWorldLimit(szBullet,WORLD_LIMIT_NULL,WORLD_LEFT, WORLD_TOP, WORLD_RIGHT, WORLD_BOTTOM);  // �����ӵ�����߽�
    // ������ײģʽ
    dSetSpriteCollisionSend(szBullet,true);
    dSetSpriteCollisionReceive(szBullet,true);

    // ��ȡ̹������ֵ
    fPosX = dGetSpritePositionX(szName);
    fPosY = dGetSpritePositionY(szName);

    // ����̹�˳��򣬽��ӵ�������̹��ǰ��1����λ�������ӵ��ٶ����ñ�̹�˿�һЩ
    switch(iDir)
    {
    case 0:
        fPosY -= dGetSpriteHeight(szName)/2 + 1;
        fSpeedX = 0;
        fSpeedY =-BULLET_SPEED;
        break;
    case 1:
        fPosX += dGetSpriteWidth(szName)/2 + 1;
        fSpeedX = BULLET_SPEED;
        fSpeedY = 0;
        break;
    case 2:
        fPosY += dGetSpriteHeight(szName)/2 + 1;
        fSpeedX = 0;
        fSpeedY = BULLET_SPEED;
        break;
    case 3:
        fPosX -= dGetSpriteWidth(szName)/2 + 1;
        fSpeedX = -BULLET_SPEED;
        fSpeedY = 0;
        break;
    }
    dSetSpritePosition(szBullet, fPosX, fPosY);
    dSetSpriteRotation(szBullet, iDir*90);
    dSetSpriteLinearVelocity(szBullet, fSpeedX, fSpeedY);

    // �����ӵ���ָ������������뵽������
    Weapon * pBullet = (Weapon*)malloc(sizeof(Weapon));
    pBullet->iDir = iDir;   // �ӵ������̹�˳���һ��
    sprintf(pBullet->szName, szBullet);
    pBullet->fPosX = fPosX;
    pBullet->fPosY = fPosY;
    pBullet->fSpeedX = fSpeedX;
    pBullet->fSpeedY = fSpeedY;
    pBullet->iType = iType;
    pBullet->iHp  = 1;

    AddToList(pBullet);

}

void CreateEnemyTanks()
{
    // ÿ�γ���1��̹�ˣ��������ڵ�һ�У������������ǰ�治�����ϰ�
    float	fPosX, fPosY;
    char	szName[128];
    int		iDir;

    Weapon* tank = (Weapon*)malloc(sizeof(Weapon));

    fPosY = -20;  // ͳһ�����ڵ�һ��
    iDir = 2;	  // ����ͳһ����

    // ���ǰ�����ϰ�����������λ��
    int j;
    do
    {
        j = dRandomRange(0, 10);
    }
    while(g_iMap[1][j] == 1);


    fPosX = -24 + j*4;

    sprintf(szName, "tank%d", g_iNum++);
    dCloneSprite("enemy", szName);
    dSetSpritePosition(szName, fPosX, fPosY);
    dSetSpriteRotation(szName, iDir*90);
    dSetSpriteLinearVelocityY(szName, TANK_SPEED);
    // ������ײ
    dSetSpriteCollisionSend(szName, true);
    dSetSpriteCollisionReceive(szName, true);
    // ��������߽�
    dSetSpriteWorldLimit(szName, WORLD_LIMIT_NULL, WORLD_LEFT, WORLD_TOP, WORLD_RIGHT, WORLD_BOTTOM);

    // ��ָ��ڵ���뵽������
    strcpy(tank->szName,  szName);
    tank->iType = ENEMYTANK;
    tank->iDir = iDir;
    tank->fRotateTime = ROTATE_TIME;
    tank->iHp = 1;
    tank->fFireTime = FIRE_TIME;

    AddToList(tank);

}
