OUTPUT_FORMAT(pe-i386)
ENTRY(_kernel_main)

SECTIONS
{
    . = 0x9000;
    .text : { *(.text) }
    .data : { *(.data) }
    .bss  : { *(.bss) *(COMMON) }
}