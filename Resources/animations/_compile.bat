cd %1

del assetdata.png /S /Q
del assetdata.plist /S /Q

..\sspack.exe ./

cd ..