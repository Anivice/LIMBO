    [bits 32]

    pusha
    mov eax, 0x01
    mov ebx, 'A'
    xor ecx, ecx
    xor edx, edx
    xor edi, edi
    xor esi, esi
    xor ebp, ebp

    int 0x80
    popa
    jmp $
