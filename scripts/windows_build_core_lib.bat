::
:: File:	windows_build_core_lib.bat
:: Created on:	2021 Aug 07
:: Autor:	Davit Kalantaryan (davit.kalantaryan@gmail.com)
:: Notice:	call this from developers command prompt
::

@echo off
setlocal EnableDelayedExpansion enableextensions

:: some definations
set "Platform=x64"

set  scriptDirectory=%~dp0
set  currentDirectory=%cd%
cd /D "%scriptDirectory%.."
set "repositoryRoot=%cd%\"

call .\contrib\event_loop_invoker\contrib\cinternal\scripts\windows_parse_key_value_pairs_file.bat ENVIRONMENT

if not defined QTDIR (
    if not defined qtRoot (
        if defined FOCUST_QT_ROOT_DIR (
            set "qtRoot=%FOCUST_QT_ROOT_DIR%"
        ) else (
            set "qtRoot=C:\Qt\6.6.1"
        )
    )
    if /i "%Platform%" == "x64" (
        set "QTDIR=!qtRoot!\msvc2019_64"
    ) else (
        set "QTDIR=!qtRoot!\msvc2019"
    )
)
echo QTDIR is !QTDIR!

if /i "!Platform!"=="x86" (
    set PlatformTarget=x86
) else (
    set PlatformTarget=x86_!Platform!
)

if /i "!VSCMD_ARG_TGT_ARCH!"=="!Platform!" (
    echo "VsDevCmd already set to !Platform!"
) else (
    echo "calling VsDevCmd in the !scriptDirectory!!scriptName!"
    rem call VsDevCmd -arch=!PlatformTarget!
    cd /D "%VCINSTALLDIR%Auxiliary\Build"
    call vcvarsall.bat !PlatformTarget!
    cd /D %repositoryRoot%
)
if not "!ERRORLEVEL!"=="0" (exit /b !ERRORLEVEL!)

call "%QTDIR%\bin\qtenv2.bat"
if not "!ERRORLEVEL!"=="0" (exit /b !ERRORLEVEL!)

cd /D "!repositoryRoot!prj\core\libinput_monitor_qt"
if not "!ERRORLEVEL!"=="0" (exit /b !ERRORLEVEL!)
if exist ".qmake.stash" del ".qmake.stash"
call "%QTDIR%\bin\qmake" CONFIG+=release CONFIG-=debug
if not "!ERRORLEVEL!"=="0" (exit /b !ERRORLEVEL!)
call nmake /f Makefile.%libNameBase%.win_%Platform%.!Confilguration!

exit /b !ERRORLEVEL!

endlocal
