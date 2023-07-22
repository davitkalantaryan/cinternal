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
set "repositoryRootBase=%cd%"
set "repositoryRoot=%cd%\"

set /p envFileContentBase=<!repositoryRoot!ENVIRONMENT

set "varname="
set "exportVars="

for %%a in (%envFileContentBase%) do (
    if not defined varname (
        set "varname=%%a"
    ) else (
	set "!varname!=%%a"
	set "exportVars=!exportVars! & set "!varname!=%%a""
	set "varname="
    )
)


endlocal & (
    set "focustCommonRepositoryRoot=%repositoryRootBase%"
) %exportVars%
