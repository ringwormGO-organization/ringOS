
bits 32
section .text
        align   4
        dd 0x1BADB002
        dd 0x00
        dd - (0x1BADB002+0x00)
        
global start
extern shell           ; this function is gonna be located in kernel.c
start:
        cli             ;clear the interrupts
        call shell      ;send processor to continue execution
        hlt             ; halt the cpu
