@echo off

set Rn_ProjectName=Kernel
set Rn_ProjectDir=Kernel
set Rn_ProjectOutName=kernel.bin
set Rn_ProjectBinDir=%Rn_BinDir%\%Rn_ProjectName%
set Rn_ProjectObjDir=%Rn_ObjDir%\%Rn_ProjectName%

if not exist %Rn_ProjectBinDir% mkdir %Rn_ProjectBinDir%
if not exist %Rn_ProjectObjDir% mkdir %Rn_ProjectObjDir%

gcc -g -m32 -c -ffreestanding -o %Rn_ProjectObjDir%\kernel.o %Rn_ProjectDir%\kernel.c -lgcc
ld -mi386pe -T %Rn_ProjectDir%\kernel.ld -nostdlib --nmagic -o %Rn_ProjectObjDir%\kernel.elf %Rn_ProjectObjDir%\kernel.o
objcopy -O binary %Rn_ProjectObjDir%\kernel.elf %Rn_ProjectBinDir%\%Rn_ProjectOutName%