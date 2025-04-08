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

set "destinationPath=%1"
set "pdbFilesDir=%2"

echo destinationPath=%destinationPath%

set  scriptDirectory=%~dp0
set  currentDirectory=%cd%
cd /D "%scriptDirectory%.."
set "repositoryRoot=%cd%\"
echo repositoryRoot=%repositoryRoot%

call .\scripts\windows_parse_key_value_pairs_file.bat ENVIRONMENT
cd /D "%currentDirectory%"

cd /D "%destinationPath%"
if not "!ERRORLEVEL!"=="0" (exit /b !ERRORLEVEL!)
copy /Y "%repositoryRoot%sys\win_%Platform%\!Confilguration!\lib\%libNameBase%%cinternal_version_major%.dll" .
copy /Y "%repositoryRoot%sys\win_%Platform%\!Confilguration!\lib\%libNameBase%%cinternal_version_major%.lib" %libNameBase%.lib

cd /D "%pdbFilesDir%"
if not "!ERRORLEVEL!"=="0" (exit /b !ERRORLEVEL!)
copy /Y "%repositoryRoot%sys\win_%Platform%\!Confilguration!\lib\%libNameBase%%cinternal_version_major%.pdb" .

exit /b !ERRORLEVEL!

endlocal
