[bits 16]
; Variables
ERROR_MSG        db "Error!" , 0
BOOT_DRIVE:      db 0

VIDEO_MEMORY_SEG equ 0xb800
WHITE_ON_BLACK   equ 0x0f

start:
    cli
    xor ax, ax
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov [BOOT_DRIVE], dl
    mov bp, 0x8000
    mov sp, bp
    mov bx, 0x9000
    mov dh, 5
    mov dl, [BOOT_DRIVE]
    call set_graphics_mode_on
    call load_kernel
    call enable_A20
	
    lgdt [gdtr]
    mov eax, cr0
    or al, 1
    mov cr0, eax
    jmp CODE_SEG:kernel_begin

set_graphics_mode_on:
    mov ax, 0013h
    int 10h
    ret

load_kernel:
							; load DH sectors to ES:BX from drive DL
    push dx             	; Store DX on stack so later we can recall
							; how many sectors were request to be read ,
							; even if it is altered in the meantime
    mov ah , 0x02       	; BIOS read sector function
    mov al , dh         	; Read DH sectors
    mov ch , 0x00       	; Select cylinder 0
    mov dh , 0x00       	; Select head 0
    mov cl , 0x02       	; Start reading from second sector ( i.e.
							; after the boot sector )
    int 0x13            	; BIOS interrupt
    jc load_kernel_error    ; Jump if error ( i.e. carry flag set )
    pop dx              	; Restore DX from the stack
    cmp dh , al         	; if AL ( sectors read ) != DH ( sectors expected )
    jne load_kernel_error   ; display error message
    ret
load_kernel_error :
    mov bx , ERROR_MSG
    call print_string
    hlt

; prints a null - terminated string pointed to by EDX
print_string :
    pusha
    push es

    push VIDEO_MEMORY_SEG
    pop es
    xor di, di
print_string_loop :
    mov al , [ bx ]
    mov ah , WHITE_ON_BLACK
    cmp al , 0
    je print_string_done
    mov word [es:di], ax
    add bx , 1
    add di , 2
    jmp print_string_loop

print_string_done :
    pop es
    popa
    ret
	
%include "Boot/a20.inc"
%include "Boot/gdt.inc"

[bits 32]
kernel_begin:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
	
    mov ebp, 0x90000
    mov esp, ebp
	
    call 0x9000	
    cli
kernel_end:
    hlt
    jmp kernel_end

[bits 16]
times 510-($-$$) db 0
db 0x55
db 0xAA