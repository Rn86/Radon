%macro ISR_NOERRCODE 1
    global RnInteruptServiceRoutine_%1
    RnInteruptServiceRoutine_%1:
        cli
        push byte 0
        push byte %1
        jmp RnInteruptServiceRoutineInternal
%endmacro

%macro ISR_ERRCODE 1
    global RnInteruptServiceRoutine_%1
    RnInteruptServiceRoutine_%1:
        cli
        push byte %1
        jmp RnInteruptServiceRoutineInternal
%endmacro

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

ISR_NOERRCODE 127	; system call

RnInteruptServiceRoutineInternal:

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

	extern RnInteruptServiceRoutine
    call RnInteruptServiceRoutine

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
