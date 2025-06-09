GPU_REGISTER_INDEX      equ 0x3d4
GPU_CURSOR_H8_BIT       equ 0x0e
GPU_CURSOR_L8_BIT       equ 0x0f
GPU_INDEXED_REG_IO      equ 0x3d5

[bits 16]                                   ; 16-bit mode

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  _____  _____   ____   _____ _____            __  __   _    _ ______          _____  ______ _____   ;;
;; |  __ \|  __ \ / __ \ / ____|  __ \     /\   |  \/  | | |  | |  ____|   /\   |  __ \|  ____|  __ \  ;;
;; | |__) | |__) | |  | | |  __| |__) |   /  \  | \  / | | |__| | |__     /  \  | |  | | |__  | |__) | ;;
;; |  ___/|  _  /| |  | | | |_ |  _  /   / /\ \ | |\/| | |  __  |  __|   / /\ \ | |  | |  __| |  _  /  ;;
;; | |    | | \ \| |__| | |__| | | \ \  / ____ \| |  | | | |  | | |____ / ____ \| |__| | |____| | \ \  ;;
;; |_|    |_|  \_\\____/ \_____|_|  \_\/_/    \_\_|  |_| |_|  |_|______/_/    \_\_____/|______|_|  \_\ ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
segment head align=16 vstart=0
    dw _program_end                         ; program length                                    +0
    dw _entry_point                         ; program entry point(index) in code segmentation   +2
    dw _data_start                          ; data segmentation start point                     +4
    dw _data_end                            ; data segmentation end point                       +6
    dw _code_start                          ; code segmentation start point                     +8
    dw _code_end                            ; code segmentation end point                       +10
    dw _stack_start                         ; stack segmentation start point                    +12
    dw _stack_end                           ; stack segmentation end point                      +14

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;   _____ ____  _____  ______    _____ ______ _____ __  __ ______ _   _ _______  ;;
;;  / ____/ __ \|  __ \|  ____|  / ____|  ____/ ____|  \/  |  ____| \ | |__   __| ;;
;; | |   | |  | | |  | | |__    | (___ | |__ | |  __| \  / | |__  |  \| |  | |    ;;
;; | |   | |  | | |  | |  __|    \___ \|  __|| | |_ | |\/| |  __| | . ` |  | |    ;;
;; | |___| |__| | |__| | |____   ____) | |___| |__| | |  | | |____| |\  |  | |    ;;
;;  \_____\____/|_____/|______| |_____/|______\_____|_|  |_|______|_| \_|  |_|    ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
segment _code_head align=16
_code_start:

segment code align=16 vstart=0
print: ;print_msg(si=null terminated msg)
    pusha
    .print_hello:
        mov         ah,                     0x0E
        mov         al,                     [ds:si]
        ; check if al is null
        cmp         al,                     0x00
        ; is null, exit
        je          .print_hello_end
        ; not null, print
        int         0x10
        inc         si
        jmp         .print_hello
    .print_hello_end:
    popa
    ret

print_num: ;print_num(ax=num,bx=is_base16?, 0 is base 10 else base 16)
    pusha
    xor             cx,                     cx
    cmp             bx,                     0
    je              .base10
    mov             bx,                     16
    jmp             .loop
    .base10:
    mov             bx,                     10
    .loop:
        xor         dx,                     dx
        div         bx
        cmp         ax,                     0
        je          .exit
        push        dx
        inc         cx
        jmp         .loop
    .exit:
    push            dx
    inc             cx

    .print:
        pop         ax
        mov         ah,                     0x0E
        add         al,                     '0'
        cmp         al,                     '9'+1
        jl          .skip
        add         al,                     7
        .skip:
        int         0x10
    loop .print

    popa
    ret

set_descriptor: ; set_descriptor(%eax=baseline,%ebx=boundary,%ecx=attribute, %fs:%si=target)
    push        eax
    push        ebx
    push        ecx
    push        edx
    push        fs
    push        si

    ; boundary
    mov         edx,                    ebx                 ; read boundary to edx
    mov         word [fs:si+0x00],      dx                  ; boundary 0-15
    shr         edx,                    16                  ; move higher 16 bits downwards
    and         dx,                     0xF                 ; only last 4bits are valid
    mov word    [fs:si+0x06],           dx                  ; boundary 16-19

    ; baseline
    mov         edx,                    eax                 ; read baseline to edx
    mov word    [fs:si+0x02],           dx                  ; baseline bit 0-15
    shr         edx,                    16                  ; move higher 16 bits downwards
    mov byte    [fs:si+0x04],           dl                  ; baseline bit 16-23
    mov byte    [fs:si+0x07],           dh                  ; baseline bit 24-31

    ; attribute
    mov         edx,                    ecx
    and         dh,                     0x0F                ; attribute bites is 12bits
    mov byte    [fs:si+0x05],           dl                  ; attribute bit 0-7
    mov byte    dl,                     [fs:si+0x06]        ; loads [6]
    shl         dh,                     4                   ; move last 4bits to higher 4bits
    or          dh,                     dl                  ; concentrate last 4bits from boundary to dh
    mov byte    [fs:si+0x06],           dh                  ; attribute bit 0-7, and boundary highest 4bits

    pop         si
    pop         fs
    pop         edx
    pop         ecx
    pop         ebx
    pop         eax
    ret

read_one_sector: ; read_disk(ch=C, dh=H, cl=S)
    pusha
    mov             ah,                     0x00    ; INT 13h, function 00h = reset
    mov             dl,                     0x00    ; drive 0 = A:
    int             0x13                            ; ignore errors for now
    popa
    pusha

    mov             ah,                     0x02    ; function 02h = read sectors
    mov             al,                     1       ; AL = how many 512-byte sectors
;    mov             ch,                     0x00    ; CH = cylinder 0
;    mov             cl,                     1      ; CL = sector 1
;    mov             dh,                     0x00    ; DH = head 0
    mov             dl,                     0x00    ; DL = drive 0 (A:)

    ; buffer: es:bx
    mov             bx,                     di
    int             0x13

    jc              .disk_error

    popa
    ret

.disk_error:
    cli
    mov         si,                     floppy_disk_err
    call        print
    xor         al,                     al
    shr         ax,                     8
    call        print_num
    hlt
    jmp         $

lba_to_chs: ; (ax=lba)->(ch=C, dh=H, cl=S)
    push    ax
    push    bx
    mov     bx,     18
    xor     dx,     dx
    div     bx
    inc     dx
    mov     cl,     dl
    xor     dx,     dx
    mov     bx,     2
    div     bx
    ; H->dl
    ; C->al
    mov     ch,     al
    mov     dh,     dl
    pop     bx
    pop     ax
    ret

; 18 + 32 cylinders + 11 sectors
_entry_point: ; _entry_point()
    pusha
    push        es
    push        ds
    push        ss

    ; print greeting message:
    mov         si,                     greet
    call        print

    mov ah, 0x01     ; INT10h, AH=01h → set cursor shape
    mov ch, 0x20     ; start scanline = 32 (beyond 0–15)
    mov cl, 0x00     ; end scanline   =   0
    int  0x10        ; cursor disabled


    mov         ax,                     0x9E0
    mov         es,                     ax
    xor         bx,                     bx
    mov         ax,                     18
    .loop:
        xor     di,                     di
        call    lba_to_chs
        call    read_one_sector

        mov     si,                     fda_msg
        call    print
        xor     bx,                     bx
        call    print_num
        mov     si,                     fda_msg2
        call    print
        push    ax
        mov     ax,                     1199+18
        xor     bx,                     bx
        call    print_num
        pop     ax
        mov     si,                     fda_endl
        call    print

        inc     ax

        cmp     ax,                     1199+18
        jg      .end_loop
        mov     bx,                     es
        add     bx,                     512/16
        mov     es,                     bx
        jmp     .loop
    .end_loop:

    mov   ah, 0x01      ; BIOS → set cursor shape
    mov   ch, 0x00      ; start scanline = 0
    mov   cl, 0x0F      ; end   scanline = 15
    int   0x10

    mov         si,                     fda_nl
    call        print

    cli
    ; load GDT location to %eax
    mov         ax,                     gdt             ; move GDT segment offset to ax
    shr         ax,                     4               ; >> 4, so ax is now segment address
    mov         bx,                     ds              ; read ds to bx
    add         ax,                     bx              ; adds ds to ax, so ax is now the actual segment address
    mov         es,                     ax              ; move the actual segment address to %es

    ; #0: NULL
    mov dword   es:[0x00],              0x00000000
    mov dword   es:[0x04],              0x00000000

    ; baseline:     0x00
    ; limit:        0xFFFFF
    ; attribute:    0xC92 -> [1] [1] [0] [0]        [1] [0 0] [1]        [0010]
    ;                         │   │   │   │          │    │    │           │
    ;                         │   │   │   │          │    │    │           └─> TYPE [X][E/C][W/R][A]
    ;                         │   │   │   │          │    │    │                Code Segment:
    ;                         │   │   │   │          │    │    │                    - X: 1: Code Segment, 0: Data Segment
    ;                         │   │   │   │          │    │    │                    - C: Privilege Compliance. 1 allows unprivileged code to execute this region
    ;                         │   │   │   │          │    │    │                    - R: Readable (0 unreadable, 1 readable)
    ;                         │   │   │   │          │    │    │                    - A: Accessed, Marked by CPU automatically
    ;                         │   │   │   │          │    │    │                Data Segment:
    ;                         │   │   │   │          │    │    │                    - X: 1: Code Segment, 0: Data Segment
    ;                         │   │   │   │          │    │    │                    - E: 1: Expand Downward, 0: Expand Upwards (since segment start)
    ;                         │   │   │   │          │    │    │                    - W: 1: Writable, 0: Write-Protected
    ;                         │   │   │   │          │    │    │                    - A: Accessed, Marked by CPU automatically
    ;                         │   │   │   │          │    │    │
    ;                         │   │   │   │          │    │    └─> System (Descriptor Type)
    ;                         │   │   │   │          │    │             0 being system
    ;                         │   │   │   │          │    │             1 being code/data(stack is data) segment
    ;                         │   │   │   │          │    └──────> DPL, Descriptor Privilege Level
    ;                         │   │   │   │          └───────────> Segment Present, used as swap flag
    ;                         │   │   │   │
    ;                         │   │   │   └─> Available (Unused by CPU)
    ;                         │   │   └─────> 64bit indicator, 0 in 32bit mode
    ;                         │   └─────────> D/B, default operation size
    ;                         │                 (set to 1 to indicate 32bit)
    ;                         └─────────────> Granularity (4KB?)
    ;

    ; put es in fs
    mov         dx,                     es
    mov         fs,                     dx

    ; Flat Mode:
    ; #1, data segment
    xor         eax,                    eax             ; baseline: 0x00
    mov         ebx,                    0xFFFFF         ; limit: 4G
    mov         ecx,                    0xC92           ; Attribute: 1100 1001 0010
    mov         si,                     8               ; descriptor is at fs:8
    call        set_descriptor

    ; #2, code segment
    xor         eax,                    eax             ; baseline: 0x00
    mov         ebx,                    0xFFFFF         ; limit: 4G
    mov         ecx,                    0xC9A           ; attr: 1100 1001 1010
    mov         si,                     16              ; descriptor is at fs:16
    call        set_descriptor

    ; #3, current code segment
    xor         eax,                    eax
    mov         ax,                     cs              ; baseline: current segment
    shl         eax,                    4               ; shift left 4 bits
    mov         ebx,                    0xFFFF          ; limit: 64KB
    mov         ecx,                    0x49A           ; attr: 0100 1001 1000 : 32bit, Segment Present, DPL=0, x---
    mov         si,                     24              ; descriptor is at fs:24
    call        set_descriptor

    ; #4, stack segment
    xor         eax,                    eax             ; baseline
    mov         ax,                     ds
    shl         eax,                    4
    add         ax,                     stack_temp
    mov         ebx,                    0x1FF           ; limit: 0x1FF
    mov         ecx,                    0x496           ; attr: 0100 1001 0110
    mov         si,                     32              ; descriptor is at fs:32
    call        set_descriptor

    ; #5, stack segment
    xor         eax,                    eax             ; baseline
    mov         ebx,                    0xFFFFF         ; limit: 4GB
    mov         ecx,                    0xC96           ; attr: 1100 1001 0110
    mov         si,                     40              ; descriptor is at fs:40
    call        set_descriptor

    ; GDT descriptor:
    mov word    [gdt_boundary],         6 * 8 - 1       ; table boundary for 5 entries
    xor         eax,                    eax
    mov         ax,                     fs              ; table base
    shl         eax,                    4               ; convert to linear address
    mov dword   [gdt_base],             eax

    ; load descriptor
    lgdt        [ds:gdt_boundary]

    ; disable A20
    in          al,                     0x92
    or          al,                     0000_0010B
    out         0x92,                   al

    ; backups
    xor         ebx,                    ebx
    xor         ecx,                    ecx
    mov         bx,                     ds
    mov         cx,                     cs

    ; disable interrupt
    cli
    mov         eax,                    cr0
    or          eax,                    1               ; enable Protected Mode
    mov         cr0,                    eax

    ; Enter 32bit Protected Mode:
    jmp  dword  0x0018:flush16      ; use jmp to force clear CPU cache generated in 16bit mode
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  ____ ___  ____  _ _     _____           _            _           _   __  __           _       ;;
;; |___ \__ \|  _ \(_) |   |  __ \         | |          | |         | | |  \/  |         | |      ;;
;;   __) | ) | |_) |_| |_  | |__) | __ ___ | |_ ___  ___| |_ ___  __| | | \  / | ___   __| | ___  ;;
;;  |__ < / /|  _ <| | __| |  ___/ '__/ _ \| __/ _ \/ __| __/ _ \/ _` | | |\/| |/ _ \ / _` |/ _ \ ;;
;;  ___) / /_| |_) | | |_  | |   | | | (_) | ||  __/ (__| ||  __/ (_| | | |  | | (_) | (_| |  __/ ;;
;; |____/____|____/|_|\__| |_|   |_|  \___/ \__\___|\___|\__\___|\__,_| |_|  |_|\___/ \__,_|\___| ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    [bits 32]
flush16:
    ; first, we need to get the flat address of our data segment inside loader
    ; first, we flat mode for data sectors
    mov             eax,                    0x08    ; 1st, flat mode data segments
    mov             ds,                     eax
    mov             es,                     eax
    mov             fs,                     eax
    mov             gs,                     eax

    ; we just use a temporary stack frame. stage 2 loader is responsible for setting up 32bit protected mode
    ; and load necessary data and environments to execute kernel code, this stack frame will be ditched anyway
    mov             eax,                    0x20    ; 4th, temporary stack space
    mov             ss,                     eax
    mov             esp,                    0x1FF

    ; now, we convert the code segment, current temporary cs (#3), to flat mode
    ; so that eip is pointed to the actual physical address
    ; ebx -> data segment -> edi (flat)
    ; ecx -> code segment -> ecx (flat)
    mov             edi,                    ebx
    shl             edi,                    4
    shl             ecx,                    4
    add             ecx,                    flat_cs_mode
    mov dword       [es:edi+flush16_ptr],   ecx
    jmp far         [es:edi+flush16_ptr]

flat_cs_mode:
    ; print notification
    mov             eax,                    msg_done
    call            dsprint

    ; print 32 bit protected mode loader greeting message
    mov             esi,                    edi
    add             esi,                    greet32
    mov             ebp,                    0x71
    call            puts

    ; setup dummy IDT
    mov             eax,                    initialize_interrupt
    call            dsprint

    mov             eax,                    idt_start
    add             eax,                    edi
    mov             [es:edi+idt_descriptor_idt_start], eax
    lidt            [es:edi+idt_descriptor]

    mov             ecx,                    256
    mov             ebp,                    idt_start
    add             ebp,                    edi
    .fill_idt:
        mov word    [es:ebp    ],           (iret_stub-$$) & 0xFFFF
        mov word    [es:ebp + 2],           0x18                        ; loader segment
        mov byte    [es:ebp + 4],           0                           ; reserved
        mov byte    [es:ebp + 5],           0x8E                        ; P=1,DPL=0,Type=14 (32-bit interrupt gate)
        mov word    [es:ebp + 6],           ((iret_stub-$$) >> 16) & 0xFFFF
        add         ebp,                    8
    loop .fill_idt
    sti

    call            print_done
    ; now we load the actual kernel.
    ; kernel is a C non-PIE program mapped itself to 1MB-2MB
    ; with first 640KB being the code section, and higher 384KB being the data section
    mov             eax,                    prepare_to_move_kernel
    call            dsprint
    mov             ecx,                    654335-40448+1
    mov             esi,                    0x9E00
    mov             edi,                    1024*1024
    cld
    rep movsb

    ; setup stack space
    mov             eax,                    0x28
    mov             ss,                     eax
    mov             esp,                    0x9FBFF     ; previously 640KB kernel cache
    xor             eax,                    eax
    xor             ebx,                    ebx
    xor             ecx,                    ecx
    xor             edx,                    edx
    xor             ebp,                    ebp
    xor             esi,                    esi
    xor             edi,                    edi
    jmp dword       0x0010:0x100000

    cli
    .@@1: hlt
    jmp             .@@1

iret_stub:
    iret

dsprint: ;(msg=eax)
    pusha
    mov             esi,                    edi
    add             esi,                    eax
    mov             ebp,                    0x07
    call            puts
    popa
    ret

print_done:
    pusha
    mov             esi,                    edi
    add             esi,                    done
    mov             ebp,                    0x07
    call            puts
    popa
    ret

putn: ; putn(eax=number)
    pusha
    xor             ecx,                    ecx
    mov             ebx,                    10
    .loop:
        xor         edx,                    edx
        div         ebx
        cmp         eax,                    0
        je          .exit
        push        edx
        inc         ecx
        jmp         .loop
    .exit:
    push            edx
    inc             ecx

    .print:
        pop         eax
        add         eax,                    '0'
        call        putc
    loop .print

    popa
    ret

puts: ; puts(ds:esi=msg)
    pusha
    xor             eax,                    eax
    .loop:
        mov byte    al,                     [ds:esi]
        cmp         al,                     0x00
        je          .exit
        call        putc
        inc         esi
        jmp         .loop
    .exit:
    popa
    ret

get_cursor: ; get_cursor()->eax
    xor             eax,                    eax
    push            edx

    ; now, point the GPU register index to the cursor register (higher 8 bit)
    mov             dx,                     GPU_REGISTER_INDEX
    mov             al,                     GPU_CURSOR_H8_BIT
    out             dx,                     al

    ; now, read from GPU register IO port, which is cursor register (higher 8 bit)
    mov             dx,                     GPU_INDEXED_REG_IO
    in              al,                     dx

    mov             ah,                     al

    ; now, point the GPU register index to the cursor register (lower 8 bit)
    mov             dx,                     GPU_REGISTER_INDEX
    mov             al,                     GPU_CURSOR_L8_BIT
    out             dx,                     al

    ; now, read from GPU register IO port, which is cursor register (lower 8 bit)
    mov             dx,                     GPU_INDEXED_REG_IO
    in              al,                     dx

    pop             edx
    ret

set_cursor: ; set_cursor(eax)
    push            edx
    push            ebx

    mov             ebx,                    eax                         ; save ax to bx

    ; now, point the GPU register index to the cursor register (higher 8 bit)
    mov             dx,                     GPU_REGISTER_INDEX
    mov             al,                     GPU_CURSOR_H8_BIT
    out             dx,                     al

    ; now, read from GPU register IO port, which is cursor register (higher 8 bit)
    mov             dx,                     GPU_INDEXED_REG_IO
    mov             al,                     bh
    out             dx,                     al

    ; now, point the GPU register index to the cursor register (lower 8 bit)
    mov             dx,                     GPU_REGISTER_INDEX
    mov             al,                     GPU_CURSOR_L8_BIT
    out             dx,                     al

    ; now, read from GPU register IO port, which is cursor register (lower 8 bit)
    mov             dx,                     GPU_INDEXED_REG_IO
    mov             al,                     bl
    out             dx,                     al

    pop             ebx
    pop             edx
    ret

putc:   ; putc(eax=character,[ebp=attr])
    pusha
    mov             ebx,                    eax                         ; save character to bl
    call            get_cursor                                          ; get_cursor() -> eax
    ; check if we have reached the bottom of the screen
    ; when that happens, we first, need to move the content on the screen upwards one line (+80 characters)
    ; first instance: last line and attempt a newline (ax >= 1920)
    ; check if (ax >= 1920 AND bl == 0x0A) OR (ax == 1999)
    cmp             eax,                    1920                        ; First Condition: eax >= 1920
    jl              .check_second_condition                             ; If eax < 1920, skip to second condition
    cmp             ebx,                    0x0A                        ; eax >= 1920, now check if ebx == 0x0A
    jne             .check_second_condition                             ; If ebx != 0x0A, skip to second condition
    jmp             .start_of_scrolling                                 ; Both conditions met: eax >= 1920 AND ebx == 0x0A
                                                                        ; Jump to start scrolling
    ; Second Condition: ax == 1999
    .check_second_condition:
        cmp         eax,                    1999                        ; if eax == 1999
        jne         .end_of_scrolling                                   ; If eax != 1999, jump to end_of_scrolling

    ; at here, condition met: eax == 1999
    .start_of_scrolling:

        mov         edi,                    0xB8000                     ; destination
        mov         esi,                    0xB8000 + 80 * 2            ; src: start of the second line
        mov         ecx,                    2000 - 80                   ; { 2000 (all the character on screen) - 80 (first line) } * 2
                                                                        ; == all the data on screen except for the first line
        cld                                                             ; direction
        rep movsw                                                       ; move

        ; now we need to clear all the characters at the bottom of the screen
        mov         edi,                    0xB8000 + 1920 * 2          ; dest
        mov         ecx,                    80                          ; count

        .clear_bottom:
            mov byte        [es:edi],       ' '
            inc             edi
            mov byte        [es:edi],       0x07
            inc             edi
        loop .clear_bottom

        ; reset cursor to the start of the last line
        ; if ebx != 0x0A, continue putc, else, we end putc (since we already handled 0x0A by scrolling)
        cmp         ebx,                    0x0A                        ; check if ebx is '\n'
        je          .set_cursor_when_ebx_equals_to_0x0A                 ; print '\n'
                                                                        ; if not
        mov         eax,                    1919                        ; line end at second last line
        call        set_cursor                                          ; set cursor
        jmp         .end_of_scrolling                                   ; end scrolling handling, continue to put the character
                                                                        ; move cursor to start at the bottom of the screen if ebx == 0x0A
                                                                        ; and we end our putc, since this is basically print a newline
        .set_cursor_when_ebx_equals_to_0x0A:                            ;
            mov     eax,                    1920                        ; move cursor to start at the bottom of the screen
            call    set_cursor                                          ; set cursor
            jmp     .end                                                ; finish putc, since we basically did the whole thing
    .end_of_scrolling:

    ; newline handler:
    cmp             ebx,                    0x0A                        ; if it's a newline marker
    jne             .end_newline_filter_conditions                      ; not newline, skip conditions and proceed to normal print
    push            eax                                                 ; save eax
    push            ebx                                                 ; save ebx
    xor             edx,                    edx                         ; clear edx
    mov             ebx,                    80                          ; ebx is now the number of characters of one line
    div             ebx                                                 ; eax % 80
    pop             ebx                                                 ; recover ebx
    pop             eax                                                 ; recover eax
    cmp             edx,                    0                           ; check eax mod 80 == 0
    jne             .set_cursor_to_newline                              ; not 0, then newline
    jmp             .end                                                ; is 0, skip this print

    .end_newline_filter_conditions:
    ; Normal print:
    ; reminder: eax is cursor linear location, ebx is actual ASCII code
    ; show the character
    mov             edi,                    eax                         ; move offset to edi
    shl             edi,                    1                           ; edi *= 2
    mov byte        [es:0xB8000+edi],       bl                          ; move character to bl
    mov             ebx,                    ebp                         ; get attribute
    mov byte        [es:0xB8000+1+edi],     bl                          ; set attributes

    ; set cursor at the updated location
    inc             eax                                                 ; move cursor to next location
    call            set_cursor                                          ; set cursor
    popa
    ret

    ; print '\n'
    .set_cursor_to_newline:
        ; we called get_cursor()->ax before hand, linear address is already in ax
        ; now that we already know the input character is '\n', we can discard the content inside bx
        mov         ebx,                    80
        xor         edx,                    edx

        ; we do a division, the y will be inside ax and x will be inside dx
        div         ebx

        ; now, we only care about ax(y), since x is always 0 at a new line
        inc         eax                                                 ; move to next line

        ; ax * 80 => ax, obtain the linear address
        mov         ebx,                    80
        xor         edx,                    edx
        mul         ebx

        call        set_cursor                                          ; now, we set the new location for cursor
    .end:
    popa
    ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    jmp         $
    ; unreachable code:
    [bits 16]
    pop         ss
    pop         ds
    pop         es
    popa
    retf
segment _code_tail align=16
_code_end:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  _____       _______          _____ ______ _____ __  __ ______ _   _ _______  ;;
;; |  __ \   /\|__   __|/\      / ____|  ____/ ____|  \/  |  ____| \ | |__   __| ;;
;; | |  | | /  \  | |  /  \    | (___ | |__ | |  __| \  / | |__  |  \| |  | |    ;;
;; | |  | |/ /\ \ | | / /\ \    \___ \|  __|| | |_ | |\/| |  __| | . ` |  | |    ;;
;; | |__| / ____ \| |/ ____ \   ____) | |___| |__| | |  | | |____| |\  |  | |    ;;
;; |_____/_/    \_\_/_/    \_\ |_____/|______\_____|_|  |_|______|_| \_|  |_|    ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
segment _data_head align=16
_data_start:
segment data align=16 vstart=0
greet:
    db "[LIMBO LOADER]: Loader is now reading 32bit kernel...", 0x0D, 0x0A, 0x00

fda_msg: db "[LIMBO LOADER FDA]: Reading sector ", 0x00
fda_msg2: db " / ", 0x00
fda_endl: db "  ", 0x0D, 0x00
fda_nl:  db 0x0D,0x0A, 0x00

floppy_disk_err:
    db 0x0D, 0x0A, "[LIMBO LOADER FDA]: Read floppy disk A failed, AH=", 0x0D, 0x0A, 0x00

msg_done:
    db "[LIMBO LOADER]: 32bit Protected mode is now active.", 0x0A, 0x00

greet32:
    db "================================================================================", 0x0A
    db "       LITTLE I386 MICROKERNEL BAREMETAL OS KERNEL LOADER VERSION 0.0.1         ", 0x0A
    db "================================================================================", 0x0A, 0x00

initialize_interrupt:
        db "[LIMBO LOADER]: Initializing dummy interrupt request handler...", 0x00

prepare_to_move_kernel:
        db "[LIMBO LOADER]: Move kernel data from 0x9E00-0x9FBFF to 0x100000-0x195DFF...", 0x0A, 0x00

done:   db "done.", 0x0A, 0x00

align 16, db 0
gdt: resb 64

gdt_boundary: dw 0
gdt_base: dd 0

flush16_ptr:
    dd 0        ; 32-bit offset
    dw 0x10     ; selector, 2nd one

stack_temp: resb 0x1FF

align 8
idt_start:
    times 256 dq 0       ; 256 entries × 8 bytes
idt_end:

idt_descriptor:
    dw idt_end - idt_start - 1  ; limit = size-1
idt_descriptor_idt_start:
    dd 0                ; base = linear address of table

segment _data_tail align=16
_data_end:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;   _____ _______       _____ _  __   _____ ______ _____ __  __ ______ _   _ _______  ;;
;;  / ____|__   __|/\   / ____| |/ /  / ____|  ____/ ____|  \/  |  ____| \ | |__   __| ;;
;; | (___    | |  /  \ | |    | ' /  | (___ | |__ | |  __| \  / | |__  |  \| |  | |    ;;
;;  \___ \   | | / /\ \| |    |  <    \___ \|  __|| | |_ | |\/| |  __| | . ` |  | |    ;;
;;  ____) |  | |/ ____ \ |____| . \   ____) | |___| |__| | |  | | |____| |\  |  | |    ;;
;; |_____/   |_/_/    \_\_____|_|\_\ |_____/|______\_____|_|  |_|______|_| \_|  |_|    ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
segment _stack_reserved align=16
_stack_start:
    resb 0x1FF
_stack_end:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  _____  _____   ____   _____ _____            __  __   _______       _____ _       ;;
;; |  __ \|  __ \ / __ \ / ____|  __ \     /\   |  \/  | |__   __|/\   |_   _| |      ;;
;; | |__) | |__) | |  | | |  __| |__) |   /  \  | \  / |    | |  /  \    | | | |      ;;
;; |  ___/|  _  /| |  | | | |_ |  _  /   / /\ \ | |\/| |    | | / /\ \   | | | |      ;;
;; | |    | | \ \| |__| | |__| | | \ \  / ____ \| |  | |    | |/ ____ \ _| |_| |____  ;;
;; |_|    |_|  \_\\____/ \_____|_|  \_\/_/    \_\_|  |_|    |_/_/    \_\_____|______| ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
segment tail align=16
_program_end:
    ; this is just used to fill the parts not in the alignment with 0
    times 16 db 0
