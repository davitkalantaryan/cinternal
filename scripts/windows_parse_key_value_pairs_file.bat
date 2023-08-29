::
:: repo:	    cinternal
:: file:	    windows_parse_key_value_pairs_file.bat
:: path:	    scripts\windows_parse_key_value_pairs_file.bat
:: created on:	2023 Jul 15
:: created by:	Davit Kalantaryan (davit.kalantaryan@gmail.com)
:: notice:	call this to initialize variables from ENVIRONMENT file
::

@echo off
setlocal EnableDelayedExpansion enableextensions

set /p envFileContentBase=<%1

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

endlocal %exportVars%
