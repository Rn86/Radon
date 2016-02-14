@echo off

set Rn_OutDir=%1
set Rn_Image=%2

qemu-system-i386 -fda %Rn_OutDir%\%Rn_Image%