@echo off

set Rn_Operation=%1
set Rn_ProjectName=%2
set Rn_Configuration=%3
set Rn_Platform=%4

set Rn_SolutionDir=%~dp0
set Rn_ProjectDir=%Rn_SolutionDir%%Rn_ProjectName%\

set Rn_OutDir=%Rn_SolutionDir%Bin\%Rn_Platform%\%Rn_Configuration%\
set Rn_IntDir=%Rn_SolutionDir%Obj\%Rn_Platform%\%Rn_Configuration%\%Rn_ProjectName%\

if not exist %Rn_OutDir% mkdir %Rn_OutDir%
if not exist %Rn_IntDir% mkdir %Rn_IntDir%

set Rn_c_Sources=()
set Rn_asm_Sources=()
set Rn_link_Libraries=()

call %Rn_ProjectDir%make.bat

setlocal EnableDelayedExpansion

If /I %Rn_Operation%==-b goto Rn_Build 
If /I %Rn_Operation%==-l goto Rn_Link
If /I %Rn_Operation%==-r goto Rn_Run

:Rn_Build

set "Rn_obj_Files="

for %%i in %Rn_c_Sources% do (
	i686-elf-gcc -I%Rn_ProjectDir%Include -c %Rn_ProjectDir%%%i.c -o %Rn_IntDir%%%i.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	set Rn_obj_Files=!Rn_obj_Files! %Rn_IntDir%%%i.o
)

for %%i in %Rn_asm_Sources% do (
	nasm -felf32 %Rn_ProjectDir%%%i.asm -o %Rn_IntDir%%%i.o
	set Rn_obj_Files=!Rn_obj_Files! %Rn_IntDir%%%i.o
)

ar cr %Rn_OutDir%%Rn_ProjectName%.a %Rn_obj_Files%

goto Rn_End 

:Rn_Link

set "Rn_lib_Files="

for %%i in %Rn_link_Libraries% do (
	set Rn_lib_Files=!Rn_lib_Files! %Rn_OutDir%%%i.a
)

i686-elf-gcc -T %Rn_SolutionDir%linker.ld %Rn_lib_Files% -o %Rn_OutDir%%Rn_ProjectName%.bin -ffreestanding -O2 -nostdlib -lgcc

goto Rn_End 

:Rn_Run

rmdir /s /q isodir
if not exist %Rn_OutDir%isodir\ mkdir %Rn_OutDir%isodir\
if not exist %Rn_OutDir%isodir\boot\ mkdir %Rn_OutDir%isodir\boot\
if not exist %Rn_OutDir%isodir\boot\grub\ mkdir %Rn_OutDir%isodir\boot\grub

copy %Rn_OutDir%Radon.bin %Rn_OutDir%isodir\boot\Radon.bin
copy %Rn_OutDir%grub.cfg %Rn_OutDir%isodir\boot\grub\grub.cfg

bash grub-mkrescue --output=%Rn_OutDir%Radon.iso %Rn_OutDir%isodir

qemu-system-i386 -cdrom %Rn_OutDir%Radon.iso

goto Rn_End

:Rn_End