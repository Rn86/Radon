# Radon
Operating Systems Project

Setup:
1. Download and install MinGW (https://sourceforge.net/projects/mingw/files/Installer/mingw-get-setup.exe/download), make sure binaries directory path is in %PATH% environmental variable.
2. Download and install Qemu (http://qemu.weilnetz.de/w32/qemu-w32-setup-20151216.exe), make sure binaries directory path is in %PATH% environmental variable.
3. Download and install Nasm (http://nasm.us/pub/nasm/releasebuilds/2.11.08/win32/nasm-2.11.08-installer.exe), make sure binaries directory path is in %PATH% environmental variable.



Commands:
1. make boot         - builds bootloader
2. make kernel       - builds kernel
3. make image        - build kernel and bootloader and makes an image.
4. run               - creates an image and runs Qemu.
