@echo off

echo ***************************************************************
echo:
echo                  Copying Firmwares for Release
echo:
echo ***************************************************************

md %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release
cd %USERPROFILE%\Documents\GitHub\Tasmota_KNX\.pioenvs

copy tasmota-minimal\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_minimal.bin
copy tasmota-BG\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-BG.bin
copy tasmota-BR\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-BR.bin
copy tasmota-CN\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-CN.bin
copy tasmota-CZ\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-CZ.bin
copy tasmota-DE\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-DE.bin
copy tasmota-EN\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-EN.bin
copy tasmota-ES\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-ES.bin
copy tasmota-FR\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-FR.bin
copy tasmota-GR\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-GR.bin
copy tasmota-HE\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-HE.bin
copy tasmota-HU\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-HU.bin
copy tasmota-IT\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-IT.bin
copy tasmota-KO\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-KO.bin
copy tasmota-NL\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-NL.bin
copy tasmota-PL\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-PL.bin
copy tasmota-PT\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-PT.bin
copy tasmota-RU\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-RU.bin
copy tasmota-SE\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-SE.bin
copy tasmota-SK\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-SK.bin
copy tasmota-TW\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-TW.bin
copy tasmota-TR\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-TR.bin
copy tasmota-UK\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-UK.bin
copy tasmota-DE_2MB\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-DE-2MB.bin
copy tasmota-EN_2MB\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-EN-2MB.bin
copy tasmota-ES_2MB\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-ES-2MB.bin
copy tasmota-DE_4MB\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-DE-4MB.bin
copy tasmota-EN_4MB\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-EN-4MB.bin
copy tasmota-ES_4MB\firmware.bin %USERPROFILE%\Documents\GitHub\Tasmota_KNX\release\tasmota_KNX-ES-4MB.bin

echo:
echo:
echo DONE...
echo:
pause
