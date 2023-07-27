#
# repo:			cinternal
# file:			cinternal_unit_test.windows.Makefile
# created on:	2023 Jul 23
# created by:	Davit Kalantaryan (davit.kalantaryan@desy.de)
#


MakeFileName        = cinternal_unit_test.windows.Makefile
MakeFileDir			= $(MAKEDIR)
TargetName			= cinternal_unit_test
TargetExtension		= exe
TargetCategory      = test
SrcBaseDir			= $(MakeFileDir)\..\..\..\src

LIBS				= $(LIBS) "Ws2_32.lib"
LFLAGS				= $(LFLAGS) /SUBSYSTEM:CONSOLE 

#Objects			= tool\main_cinternal_unit_test.x64_d_obj

#SourcesToCompile	=
#DirectoriesToCompile	= $(DirectoriesToCompile) nr-build\gen\cpp\sss\ssslang\antlr
DirectoriesToCompile	=
DirectoriesToCompile	= tests\unit_test
#DirectoriesToCompile	= $(DirectoriesToCompile) nr-core
DirectoriesToCompile	= $(DirectoriesToCompile) core
#DirectoriesToCompile	= $(DirectoriesToCompile) intern
#DirectoriesToCompile	= $(DirectoriesToCompile) tools\cutils_unit_test

default: unittest

unittest: __preparationForSetObjects __setObjects

!include <$(MakeFileDir)\..\..\common\common_mkfl\flagsandsys_common.windows.Makefile>
