::
:: File:	windows_build_core_lib.bat
:: Created on:	2021 Aug 07
:: Autor:	Davit Kalantaryan (davit.kalantaryan@gmail.com)
:: Notice:	call this from developers command prompt
::

@echo off
setlocal EnableDelayedExpansion enableextensions

set  scriptDirectory=%~dp0
set  currentDirectory=%cd%
cd /D "%scriptDirectory%.."
set "repositoryRoot=%cd%\"

call .\scripts\windows_parse_key_value_pairs_file.bat ENVIRONMENT

cd /D "!repositoryRoot!prj\core\libcinternal_qt"
if not "!ERRORLEVEL!"=="0" (exit /b !ERRORLEVEL!)
if exist ".qmake.stash" del ".qmake.stash"
call "%QTDIR%\bin\qmake" CONFIG+=release CONFIG-=debug
if not "!ERRORLEVEL!"=="0" (exit /b !ERRORLEVEL!)
call nmake /f Makefile.%libNameBase%.win_%Platform%.!Confilguration!

exit /b !ERRORLEVEL!

endlocal
