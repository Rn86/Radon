@echo off

set Rn_MakeInput=%1
set Rn_BinDir=Bin
set Rn_ObjDir=Obj

if not exist %Rn_BinDir% mkdir %Rn_BinDir%
if not exist %Rn_ObjDir% mkdir %Rn_ObjDir%

call %Rn_MakeInput%\make.bat
