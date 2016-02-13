@echo off

call make.bat Boot
set Rn_BootBinDir=%Rn_ProjectBinDir%
set Rn_BootOutName=%Rn_ProjectOutName%

call make.bat Kernel
set Rn_KernelBinDir=%Rn_ProjectBinDir%
set Rn_KernelOutName=%Rn_ProjectOutName%

set Rn_ProjectName=Image
set Rn_ProjectDir=Image
set Rn_ProjectOutName=radon.img
set Rn_ProjectBinDir=%Rn_BinDir%\%Rn_ProjectName%
set Rn_ProjectObjDir=%Rn_ObjDir%\%Rn_ProjectName%

if not exist %Rn_ProjectBinDir% mkdir %Rn_ProjectBinDir%
if not exist %Rn_ProjectObjDir% mkdir %Rn_ProjectObjDir%

dd if=/dev/zero of=%Rn_ProjectBinDir%\%Rn_ProjectOutName% bs=512 count=2880
dd if=%Rn_BootBinDir%\%Rn_BootOutName% of=%Rn_ProjectBinDir%\%Rn_ProjectOutName% bs=512
dd if=%Rn_KernelBinDir%\%Rn_KernelOutName% of=%Rn_ProjectBinDir%\%Rn_ProjectOutName% bs=512 seek=1