@echo off

set Rn_Operation=%1
set Rn_IntDir=%2
set Rn_OutDir=%3
set Rn_Output=%4

If /I %Rn_Operation%==-b goto Rn_Build 
If /I %Rn_Operation%==-r goto Rn_Rebuild
If /I %Rn_Operation%==-c goto Rn_Clean
echo Incorrect input & goto Rn_End

:Rn_Build
dd if=/dev/zero of=%Rn_OutDir%\%Rn_Output% bs=512 count=2880
dd if=%Rn_OutDir%\boot.bin of=%Rn_OutDir%\%Rn_Output% bs=512
dd if=%Rn_OutDir%\kernel.bin of=%Rn_OutDir%\%Rn_Output% bs=512 seek=1
goto Rn_End

:Rn_Rebuild
goto Rn_Build
goto Rn_End

:Rn_Clean
del /f /s /q %Rn_IntDir% 1>nul
del /f /s /q %Rn_OutDir% 1>nul
goto Rn_End

:Rn_End