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
set "repositoryRoot=%cd%\"


endlocal & (
    call "%scriptDirectory%windows_parse_key_value_pairs_file.bat" %repositoryRoot%ENVIRONMENT
) %exportVars%
