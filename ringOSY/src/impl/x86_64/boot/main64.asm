global long_mode_start
extern kernel_main

section .text
bits64
long_mode_start:
    ; Initlize the registers
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Start the kernel (in the main.c)
    call kernel_main
    hlt
