%macro IRQ 1
    global RnInteruptRequest_%1
    RnInteruptRequest_%1:
        cli
        push byte 0
        push byte %1
        jmp RnInteruptRequestInternal
%endmacro

IRQ 0
IRQ 1
IRQ 2
IRQ 3
IRQ 4
IRQ 5
IRQ 6
IRQ 7
IRQ 8
IRQ 9
IRQ 10
IRQ 11
IRQ 12
IRQ 13
IRQ 14
IRQ 15

RnInteruptRequestInternal:

	push eax
	push ecx
	push edx
	push ebx
	push esp
	push ebp
	push esi
	push edi

	mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

	extern RnInteruptRequest
    call RnInteruptRequest

	pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

	pop edi
	pop esi
	pop ebp
	pop esp
	pop ebx
	pop edx
	pop ecx

    add esp, 12
    sti
    iret
