@echo off

set Rn_Operation=%1
set Rn_ProjectName=%2
set Rn_Configuration=%3
set Rn_Platform=%4

set Rn_SolutionDir=%~dp0
set Rn_ProjectDir=%Rn_SolutionDir%%Rn_ProjectName%\


echo INTDIR = Obj\%Rn_Platform%\%Rn_Configuration% > %Rn_SolutionDir%projectVars.txt
echo BINDIR = Bin\%Rn_Platform%\%Rn_Configuration% >> %Rn_SolutionDir%projectVars.txt


set Rn_OutDir=%Rn_SolutionDir%Bin\%Rn_Platform%\%Rn_Configuration%\
set Rn_IntDir=%Rn_SolutionDir%Obj\%Rn_Platform%\%Rn_Configuration%\

if not exist %Rn_OutDir% mkdir %Rn_OutDir%
if not exist %Rn_IntDir% mkdir %Rn_IntDir%

if not exist %Rn_IntDir%LibC			mkdir %Rn_IntDir%LibC
if not exist %Rn_IntDir%LibC\stdio		mkdir %Rn_IntDir%LibC\stdio
if not exist %Rn_IntDir%LibC\stdlib		mkdir %Rn_IntDir%LibC\stdlib
if not exist %Rn_IntDir%LibC\string		mkdir %Rn_IntDir%LibC\string

if not exist %Rn_IntDir%Bootloader		mkdir %Rn_IntDir%Bootloader
if not exist %Rn_IntDir%Kernel			mkdir %Rn_IntDir%Kernel
if not exist %Rn_IntDir%Radon			mkdir %Rn_IntDir%Radon
if not exist %Rn_IntDir%RadonAPI		mkdir %Rn_IntDir%RadonAPI

set Rn_c_Sources=()
set Rn_asm_Sources=()
set Rn_link_Libraries=()

call %Rn_ProjectDir%make.bat

setlocal EnableDelayedExpansion

If /I %Rn_Operation%==-b goto Rn_Build 
If /I %Rn_Operation%==-r goto Rn_Run

:Rn_Build

set "Rn_obj_Files="

	echo 'tuping Radon'
	tup

goto Rn_End 

:Rn_Run

	rmdir /s /q isodir
	if not exist %Rn_OutDir%isodir\ mkdir %Rn_OutDir%isodir\
	if not exist %Rn_OutDir%isodir\boot\ mkdir %Rn_OutDir%isodir\boot\
	if not exist %Rn_OutDir%isodir\boot\grub\ mkdir %Rn_OutDir%isodir\boot\grub

	copy %Rn_OutDir%Radon.bin %Rn_OutDir%isodir\boot\Radon.bin
	copy grub.cfg %Rn_OutDir%isodir\boot\grub\grub.cfg

	bash grub-mkrescue --output=%Rn_OutDir%Radon.iso %Rn_OutDir%isodir

	qemu-system-i386 -cdrom %Rn_OutDir%Radon.iso

	goto Rn_End

:Rn_End