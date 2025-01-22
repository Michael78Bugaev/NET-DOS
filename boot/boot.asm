global start
extern kernel_main

section .text
bits 32
start:
    ; Set up stack
    mov esp, stack_top
    push ebx
    ; Call the kernel main function
    call kernel_main

    ; Halt the CPU
    hlt

section .bss
align 16
stack_bottom:
    resb 16384 ; 16 KB stack
stack_top: