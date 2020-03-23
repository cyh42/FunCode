# Microsoft Developer Studio Generated NMAKE File, Based on VCProjectVC6.dsp
!IF "$(CFG)" == ""
CFG=VCProjectVC6 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to VCProjectVC6 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "VCProjectVC6 - Win32 Release" && "$(CFG)" != "VCProjectVC6 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCProjectVC6.mak" CFG="VCProjectVC6 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VCProjectVC6 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VCProjectVC6 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "VCProjectVC6 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\..\..\Bin\Game.exe"


CLEAN :
	-@erase "$(INTDIR)\List.obj"
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VCTemplate.res"
	-@erase "..\..\..\Bin\Game.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "../../Header" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\VCProjectVC6.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\VCTemplate.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VCProjectVC6.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Winmm.lib ..\..\Src\CommonAPI_VC6.Lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Game.pdb" /machine:I386 /out:"..\..\..\Bin\Game.exe" 
LINK32_OBJS= \
	"$(INTDIR)\List.obj" \
	"$(INTDIR)\Main.obj" \
	"$(INTDIR)\VCTemplate.res"

"..\..\..\Bin\Game.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VCProjectVC6 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\..\..\Bin\Game.exe"


CLEAN :
	-@erase "$(INTDIR)\List.obj"
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VCTemplate.res"
	-@erase "$(OUTDIR)\Game.pdb"
	-@erase "..\..\..\Bin\Game.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "../../Header" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\VCProjectVC6.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\VCTemplate.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VCProjectVC6.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Winmm.lib ..\..\Src\CommonAPI_VC6.Lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Game.pdb" /debug /machine:I386 /out:"..\..\..\Bin\Game.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\List.obj" \
	"$(INTDIR)\Main.obj" \
	"$(INTDIR)\VCTemplate.res"

"..\..\..\Bin\Game.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("VCProjectVC6.dep")
!INCLUDE "VCProjectVC6.dep"
!ELSE 
!MESSAGE Warning: cannot find "VCProjectVC6.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "VCProjectVC6 - Win32 Release" || "$(CFG)" == "VCProjectVC6 - Win32 Debug"
SOURCE=..\..\Src\List.cpp

"$(INTDIR)\List.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\Src\Main.cpp

"$(INTDIR)\Main.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\VCTemplate.rc

"$(INTDIR)\VCTemplate.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

