#
# repo:			cinternal
# file:			cinternal_unit_test.windows.Makefile
# created on:	2023 Jul 23
# created by:	Davit Kalantaryan (davit.kalantaryan@desy.de)
#

# this is set automatically when needed
!IFNDEF MakeFileDir
MakeFileDir			= $(MAKEDIR)
!ENDIF
MakeFileName        = cinternal_unit_test.windows.Makefile

RepoRootDir			= $(MakeFileDir)\..\..\..
SrcBaseDir			= $(MakeFileDir)\..\..\..\src

TargetName			= cinternal_unit_test
TargetExtension		= exe
TargetCategory      = test

LINKER        		= link
PDB_FILE_PATH		= $(TargetDirectory)\$(TargetName).pdb
DEFINES       		= $(DEFINES) /D "_WINDLL" /D "_MBCS" /D "CPPUTILS_USING_STATIC_LIB_OR_OBJECTS"
INCLUDE_PATHS		= $(INCLUDE_PATHS) /I"$(RepoRootDir)\include"
CFLAGS				= $(CFLAGS) $(INCLUDE_PATHS) $(DEFINES)
CXXFLAGS			= $(CXXFLAGS) $(CFLAGS)

LIBPATHS			= $(LIBPATHS) /LIBPATH:"$(RepoRootDir)\sys\win_$(Platform)\$(Configuration)\lib"
LIBS				=
LIBS				= $(LIBS) "Ws2_32.lib"

LFLAGS				= $(LFLAGS) /OUT:"$(TargetDirectory)\$(TargetFileName)" 
LFLAGS				= $(LFLAGS) /MANIFEST /NXCOMPAT /PDB:"$(TargetDirectory)\$(TargetName).pdb" 
LFLAGS				= $(LFLAGS) /DYNAMICBASE $(LIBS) 
LFLAGS				= $(LFLAGS) /DEBUG /MACHINE:$(Platform) /INCREMENTAL  
LFLAGS				= $(LFLAGS) /SUBSYSTEM:CONSOLE /MANIFESTUAC:"level='asInvoker' uiAccess='false'" 
LFLAGS				= $(LFLAGS) /ERRORREPORT:PROMPT /NOLOGO $(LIBPATHS) /TLBID:1

#Objects			= tool\main_cinternal_unit_test.x64_d_obj

#SourcesToCompile	=
#DirectoriesToCompile	= $(DirectoriesToCompile) nr-build\gen\cpp\sss\ssslang\antlr
DirectoriesToCompile	=
DirectoriesToCompile	= tests\unit_test
#DirectoriesToCompile	= $(DirectoriesToCompile) nr-core
DirectoriesToCompile	= $(DirectoriesToCompile) core
DirectoriesToCompile	= $(DirectoriesToCompile) intern
DirectoriesToCompile	= $(DirectoriesToCompile) tools\cutils_unit_test

default: unittest


unittest: __preparationForSetObjects __setObjects


__buildGoogleTestLib:
	@cd $(MakeFileDir)
	@echo "!!!!!! 'msbuild -t:restore -p:RestorePackagesConfig=true' is not necessary anymore"

!include <$(RepoRootDir)\prj\common\common_mkfl\flagsandsys_common_private.windows.Makefile>
