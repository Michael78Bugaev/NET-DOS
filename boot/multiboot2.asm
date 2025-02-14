section .multiboot_header
header_start:
    dd 0xe85250d6                ; Magic number (Multiboot 2)
    dd 0                         ; Architecture 0 (protected mode i386)
    dd header_end - header_start ; Header length
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start)) ; Checksum

    ; Optional tags here

    ;dw 5
    ;dw 0
    ;dd 20
    ;dd 1024
    ;dd 768
    ;dd 32

    ; End tag
    dw 0    ; Type
    dw 0    ; Flags
    dd 8    ; Size
header_end: