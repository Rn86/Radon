@echo off

set Rn_ProjectName=Boot
set Rn_ProjectDir=Boot
set Rn_ProjectOutName=boot.bin
set Rn_ProjectBinDir=%Rn_BinDir%\%Rn_ProjectName%
set Rn_ProjectObjDir=%Rn_ObjDir%\%Rn_ProjectName%

if not exist %Rn_ProjectBinDir% mkdir %Rn_ProjectBinDir%
if not exist %Rn_ProjectObjDir% mkdir %Rn_ProjectObjDir%

nasm -g -f elf32 -F dwarf -o %Rn_ProjectObjDir%\boot.o %Rn_ProjectDir%\boot.asm
ld -mi386pe -Ttext=0x7c00 -nostdlib --nmagic -o %Rn_ProjectObjDir%\boot.elf %Rn_ProjectObjDir%\boot.o
objcopy -O binary %Rn_ProjectObjDir%\boot.elf %Rn_ProjectBinDir%\%Rn_ProjectOutName%