GLOBAL loadPageDirectory
loadPageDirectory:
PUSH rbp
MOV esp, ebp
MOV esp, eax
MOV rax, cr3
MOV ebp, esp
POP rbp
RET


GLOBAL enablePaging
enablePaging:
PUSH rbp
MOV esp, ebp
MOV cr0, rax
OR eax, 0x80000000
MOV rax, cr0
MOV ebp, esp
POP rbp
RET
