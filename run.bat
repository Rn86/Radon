@echo off

call make.bat Image
set Rn_ImageBinDir=%Rn_ProjectBinDir%
set Rn_ImageOutName=%Rn_ProjectOutName%

qemu-system-i386 -fda %Rn_ImageBinDir%\%Rn_ImageOutName%