[bits 64]

SECTION .text

IdleTask:
    jmp IdleTask

GLOBAL IdleTask