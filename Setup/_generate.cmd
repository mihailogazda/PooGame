echo off
echo Building game into ZIP file
echo on

REM Settings
set @zipName=Poo!.zip 
set @inputDir=..\bin
set @resDir=..\Resources
set @zipMode=-r -9
set @zipCommand=_zip.exe %@zipMode% %@zipName% 

REM remove old version
del %@zipName% /f /q

REM pack Bin directory
md Bin
xcopy %@inputDir%\*.exe Bin\*.*
xcopy %@inputDir%\*.dll Bin\*.*

%@zipCommand% "Bin\*.*"
del bin\*.* /f /q
rd bin /S /Q

REM pack Resources
md Resources
xcopy /E %@resDir%\*.png Resources\*.*
xcopy /E %@resDir%\*.mp3 Resources\*.*
xcopy /E %@resDir%\*.wav Resources\*.*
xcopy /E %@resDir%\*.xml Resources\*.*
xcopy /E %@resDir%\*.json Resources\*.*
xcopy /E %@resDir%\*.vsh Resources\*.*
xcopy /E %@resDir%\*.fsh Resources\*.*
xcopy /E %@resDir%\*.js Resources\*.*

%@zipCommand% "Resources\*.*"
del Resources\*.* /f /q
rd Resources /S /Q

REM Pack Shortcuts
xcopy ..\_start.bat *.*
%@zipCommand% "*.bat"
del *.bat /f /q

REM Pack Readme
%@zipCommand% "*.txt"

pause