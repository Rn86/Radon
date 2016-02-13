# Radon
Operating Systems Project

## Setup:
1. Download and install [MinGW](https://sourceforge.net/projects/mingw/files/Installer/mingw-get-setup.exe/download), make sure binaries directory path is in %PATH% environmental variable.
2. Download and install [Qemu](http://qemu.weilnetz.de/w32/qemu-w32-setup-20151216.exe), make sure binaries directory path is in %PATH% environmental variable.
3. Download and install [Nasm](http://nasm.us/pub/nasm/releasebuilds/2.11.08/win32/nasm-2.11.08-installer.exe), make sure binaries directory path is in %PATH% environmental variable.

## Commands:
| Command       | Description                                     |
|:--------------|:------------------------------------------------|
| make boot     | Builds bootloader                               |
| make kernel   | Builds kernel                                   |
| make image    | Build kernel and bootloader and creates an image|
| run           | Creates an image and runs Qemu                  |
