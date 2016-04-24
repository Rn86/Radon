rmdir /s /q bin\Debug\root
if not exist bin\Debug\root\ mkdir bin\Debug\root\
if not exist bin\Debug\root\boot\ mkdir bin\Debug\root\boot\
if not exist bin\Debug\root\boot\grub\ mkdir bin\Debug\root\boot\grub

copy bin\Debug\libRadon.so bin\Debug\root\boot\Radon.bin
copy grub.cfg bin\Debug\root\boot\grub\grub.cfg

bash grub-mkrescue --output=bin\Debug\Radon.iso bin\Debug\root

qemu-system-i386 -cdrom bin\Debug\Radon.iso