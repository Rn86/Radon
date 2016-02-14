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
nasm -g -f elf32 -F dwarf -o %Rn_IntDir%\boot.o boot.asm
ld -mi386pe -Ttext=0x7c00 -nostdlib --nmagic -o %Rn_IntDir%\boot.elf %Rn_IntDir%\boot.o
objcopy -O binary %Rn_IntDir%\boot.elf %Rn_OutDir%\%Rn_Output%
goto Rn_End

:Rn_Rebuild
goto Rn_Build
goto Rn_End

:Rn_Clean
del /f /s /q %Rn_IntDir% 1>nul
del /f /s /q %Rn_OutDir% 1>nul
goto Rn_End

:Rn_End