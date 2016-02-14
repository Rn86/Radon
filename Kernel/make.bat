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
gcc -g -m32 -c -ffreestanding -o %Rn_IntDir%\kernel.o kernel.c -lgcc
ld -mi386pe -T kernel.ld -nostdlib --nmagic -o %Rn_IntDir%\kernel.elf %Rn_IntDir%\kernel.o
objcopy -O binary %Rn_IntDir%\kernel.elf %Rn_OutDir%\%Rn_Output%
goto Rn_End

:Rn_Rebuild
goto Rn_Build
goto Rn_End

:Rn_Clean
del /f /s /q %Rn_IntDir% 1>nul
del /f /s /q %Rn_OutDir% 1>nul
goto Rn_End

:Rn_End