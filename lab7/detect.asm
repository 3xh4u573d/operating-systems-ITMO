SECTION .data
    res1: db "VM",10
    len1: equ $-res1
    res2: db "None",10
    len2: equ $-res2

SECTION .text
    gloval _start

_start:
    xor eax,eax
    mov eax,0x40000000
    cpuid
    cmp ecx,0x4D566572
    jne None
    cmp edx,0x65726177
    jne None
    mov edx,len1
    mov ecx,res1
    mov ebx,1
    mov eax,4
    int 0x80
    jmp finish
    None:
    mov edx,len2
    mov ecx,res2
    mov ebx,1
    mov eax,4
    int 0x80
    finish:
    xor ebx,ebx
    mov eax,1
    int 0x80