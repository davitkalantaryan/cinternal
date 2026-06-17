::
:: repo:	    cinternal
:: file:	    windows_source_parse_environment.bat
:: path:	    scripts\windows_source_parse_environment.bat
:: created on:	2023 Jul 15
:: created by:	Davit Kalantaryan (davit.kalantaryan@gmail.com)
:: notice:	call this to initialize variables from ENVIRONMENT file
::

@echo off
setlocal EnableDelayedExpansion enableextensions

set  scriptDirectory=%~dp0
cd /D "%scriptDirectory%.."
set "cinternalRepoRoot=%cd%"
set "repositoryRoot=%cinternalRepoRoot%\"


if not defined PlatformToolsetVar (
	if /i "%VisualStudioVersion%"=="18.0" set "PlatformToolsetVar=v145"
    if /i "%VisualStudioVersion%"=="17.0" set "PlatformToolsetVar=v143"
    if /i "%VisualStudioVersion%"=="16.0" set "PlatformToolsetVar=v142"
    if /i "%VisualStudioVersion%"=="15.0" set "PlatformToolsetVar=v141"

    if not defined PlatformToolsetVar (
        echo ERROR: Unsupported or missing VisualStudioVersion="%VisualStudioVersion%"
        exit /b 1
    )
)


endlocal & (
    call "%scriptDirectory%windows_parse_key_value_pairs_file.bat" "%cinternalRepoRoot%\ENVIRONMENT"
    set "PlatformToolsetVar=%PlatformToolsetVar%"
    set "cinternalRepoRoot=%cinternalRepoRoot%"
)
