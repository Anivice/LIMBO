#    .org 0x7C00
    .code16

start:
    cli
    xorw   %ax, %ax
    movw   %ax, %ds
    movw   %ax, %es

    movw   $message, %si

print_loop:
    lodsb
    cmpb   $0, %al
    je     done

    movb   $0x0E, %ah
    movb   $0x00, %bh
    movb   $0x07, %bl
    int    $0x10

    jmp    print_loop

done:
    cli

hang:
    hlt
    jmp    hang

message:
    .ascii "Hello World!"
    .byte  0


    .fill 510 - (.-start), 1, 0

    .word  0xAA55
