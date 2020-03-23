/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "List.h"
/////////////////////////////////////////////////////////////////////////////////
//
//
Weapon	*g_pHead	=	NULL;
int		 g_listSize =	0;			// �����еĽڵ���
//

/////////////////////////////////////////////////////////////////////////////
// ���������нڵ�����
int	GetListSize()
{
	return g_listSize;
}


/////////////////////////////////////////////////////////////////////////////
// ���ݾ������ơ��÷��Լ�ʱ����������һ���½ڵ㱣�浽���������һ��λ��
void AddToList(Weapon *pSprite)
{
	Weapon* pTemp = (Weapon*)malloc(sizeof(Weapon)) ;
	strcpy(pTemp->szName, pSprite->szName);	
	pTemp->fPosX = pSprite->fPosX;
	pTemp->fPosY = pSprite->fPosY;
	pTemp->fSpeedX = pSprite->fSpeedX;
	pTemp->fSpeedY = pSprite->fSpeedY;
	pTemp->iDir = pSprite->iDir;
	pTemp->iType = pSprite->iType;
	pTemp->iHp = pTemp->iHp;
	pTemp->fRotateTime = pSprite->fRotateTime;
	pTemp->fFireTime = pSprite->fFireTime;
	
	pTemp->pNext = NULL;

	Weapon* pNode = g_pHead;

	if(g_pHead == NULL) // ��ͷΪ�գ�˵���������һ���ڵ�
	{
		g_pHead = pTemp;
	}
	else{			
		while(pNode->pNext != NULL)  // ѭ��������������һ���ڵ�
		{
			pNode = pNode->pNext;
		}
		pNode->pNext = pTemp;
	}	
	g_listSize++;
	
}
/////////////////////////////////////////////////////////////////////////////////
//
// �������ֻ�ȡSprite
Weapon* FindNode( const char *szName )
{
	Weapon	*pNode	=	g_pHead;
	while( NULL != pNode )
	{
		if( strcmp( pNode->szName, szName ) == 0 )
			return pNode;

		pNode	=	pNode->pNext;
	}

	return NULL;
}


//==============================================================================
//
// ��������ɾ��Sprite
void DeleteNode( const char *szName)
{
	Weapon	*pNode	=	g_pHead;
	Weapon  *pTemp	=	NULL;

	// �������Ϊ��
	if(pNode != NULL)
	{
		if(strcmp(pNode->szName, szName)==0)  // �����ͷ����Ҫ�ҵĽڵ�
		{
			g_pHead = g_pHead->pNext;
			free(pNode);
		}
		else
		{			
			while(strcmp(pNode->pNext->szName, szName)) // �ýڵ����һ���ڵ㲻��Ҫ�ҵĽڵ�
			{				
				pNode = pNode->pNext;
			}
			pTemp = pNode->pNext;
			pNode->pNext = pNode->pNext->pNext;
			free(pTemp);
		}
	}
	g_listSize--;
}

//==============================================================================
//
// ɾ������Sprite
void DeleteList( )
{
	Weapon	*pNode				=	NULL;
	Weapon	*pNext	=	g_pHead;
	while( NULL != pNext )
	{
		pNode	=	pNext;
		pNext	=	pNext->pNext;

		// ɾ���ýڵ��Ӧ�ľ���
		dDeleteSprite(pNode->szName);

		// �ͷ��ڴ�
		free( pNode );
	};

	//
	g_listSize = 0; 
	g_pHead	=	NULL;	
}


