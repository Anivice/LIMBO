[bits 16]                                   ; 16-bit mode

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  _____  _____   ____   _____ _____            __  __   _    _ ______          _____  ______ _____  ;;
;; |  __ \|  __ \ / __ \ / ____|  __ \     /\   |  \/  | | |  | |  ____|   /\   |  __ \|  ____|  __ \ ;;
;; | |__) | |__) | |  | | |  __| |__) |   /  \  | \  / | | |__| | |__     /  \  | |  | | |__  | |__) |;;
;; |  ___/|  _  /| |  | | | |_ |  _  /   / /\ \ | |\/| | |  __  |  __|   / /\ \ | |  | |  __| |  _  / ;;
;; | |    | | \ \| |__| | |__| | | \ \  / ____ \| |  | | | |  | | |____ / ____ \| |__| | |____| | \ \ ;;
;; |_|    |_|  \_\\____/ \_____|_|  \_\/_/    \_\_|  |_| |_|  |_|______/_/    \_\_____/|______|_|  \_\;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
segment head align=16 vstart=0
    dw _program_end                         ; program length                                    +0
    dw _entry_point                         ; program entry point(index) in code segmentation   +2
    dw _data_start                          ; data segmentation start point                     +4
    dw _data_end                            ; data segmentation end point                       +6
    dw _code_start                          ; code segmentation start point                     +8
    dw _code_end                            ; code segmentation end point                       +10
    dw _stack_start                         ; stack segmentation start point                    +12
    dw _stack_end                           ; stack segmentation end point                      +14

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;   _____ ____  _____  ______    _____ ______ _____ __  __ ______ _   _ _______ ;;
;;  / ____/ __ \|  __ \|  ____|  / ____|  ____/ ____|  \/  |  ____| \ | |__   __|;;
;; | |   | |  | | |  | | |__    | (___ | |__ | |  __| \  / | |__  |  \| |  | |   ;;
;; | |   | |  | | |  | |  __|    \___ \|  __|| | |_ | |\/| |  __| | . ` |  | |   ;;
;; | |___| |__| | |__| | |____   ____) | |___| |__| | |  | | |____| |\  |  | |   ;;
;;  \_____\____/|_____/|______| |_____/|______\_____|_|  |_|______|_| \_|  |_|   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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

_entry_point: ; _entry_point()
    pusha
    push        es
    push        ds
    push        ss

    ; print greeting message:
    mov         si,                     greet
    call        print


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
    mov         ecx,                    0x498           ; attr: 0100 1001 1000 : 32bit, Segment Present, DPL=0, x---
    mov         si,                     24              ; descriptor is at fs:24
    call        set_descriptor

    ; #4, stack segment
    xor         eax,                    eax             ; baseline: 0x00
    mov         ebx,                    0xFFFFF         ; limit: 4G
    mov         ecx,                    0xC96           ; attr: 1100 1001 0110
    mov         si,                     32              ; descriptor is at fs:24
    call        set_descriptor

    ; GDT descriptor:
    mov word    [gdt_boundary],         5 * 8 - 1       ; table boundary for 5 entries
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

    ; disable interrupt
    cli
    mov         eax,                    cr0
    or          eax,                    1               ; enable Protected Mode
    mov         cr0,                    eax

    ; Enter 32bit Protected Mode:
    jmp  dword  0x0018:flush16      ; use jmp to force clear CPU cache generated in 16bit mode

    [bits 32]
flush16:
    mov         eax,                    0x08
    mov         es,                     ax

    mov byte    [es:0x0b8000],          '#'
    jmp         $

    [bits 16]

    pop         ss
    pop         ds
    pop         es
    popa
    retf                                    ; since we did a far call, we use a far return
segment _code_tail align=16
_code_end:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  _____       _______          _____ ______ _____ __  __ ______ _   _ _______ ;;
;; |  __ \   /\|__   __|/\      / ____|  ____/ ____|  \/  |  ____| \ | |__   __|;;
;; | |  | | /  \  | |  /  \    | (___ | |__ | |  __| \  / | |__  |  \| |  | |   ;;
;; | |  | |/ /\ \ | | / /\ \    \___ \|  __|| | |_ | |\/| |  __| | . ` |  | |   ;;
;; | |__| / ____ \| |/ ____ \   ____) | |___| |__| | |  | | |____| |\  |  | |   ;;
;; |_____/_/    \_\_/_/    \_\ |_____/|______\_____|_|  |_|______|_| \_|  |_|   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
segment _data_head align=16
_data_start:
segment data align=16 vstart=0
greet:
    db "                    LIMBO KERNEL LOADER VERSION 0.0.1", 0x0D, 0x0A
    db "[LIMBO LOADER]: Loader is now setting up 32bit Protected Mode.", 0x0D, 0x0A, 0x00

align 16, db 0
gdt:
resb 64

gdt_boundary:
    dw 0
gdt_base:
    dd 0

pm_ptr:         ; m16:32 structure
    dd  0       ; actual address
    dw  0x10    ; code segment selector in flat mode

segment _data_tail align=16
_data_end:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;   _____ _______       _____ _  __   _____ ______ _____ __  __ ______ _   _ _______ ;;
;;  / ____|__   __|/\   / ____| |/ /  / ____|  ____/ ____|  \/  |  ____| \ | |__   __|;;
;; | (___    | |  /  \ | |    | ' /  | (___ | |__ | |  __| \  / | |__  |  \| |  | |   ;;
;;  \___ \   | | / /\ \| |    |  <    \___ \|  __|| | |_ | |\/| |  __| | . ` |  | |   ;;
;;  ____) |  | |/ ____ \ |____| . \   ____) | |___| |__| | |  | | |____| |\  |  | |   ;;
;; |_____/   |_/_/    \_\_____|_|\_\ |_____/|______\_____|_|  |_|______|_| \_|  |_|   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
segment _stack_reserved align=16
_stack_start:
    resb 0x1FF
_stack_end:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  _____  _____   ____   _____ _____            __  __   _______       _____ _      ;;
;; |  __ \|  __ \ / __ \ / ____|  __ \     /\   |  \/  | |__   __|/\   |_   _| |     ;;
;; | |__) | |__) | |  | | |  __| |__) |   /  \  | \  / |    | |  /  \    | | | |     ;;
;; |  ___/|  _  /| |  | | | |_ |  _  /   / /\ \ | |\/| |    | | / /\ \   | | | |     ;;
;; | |    | | \ \| |__| | |__| | | \ \  / ____ \| |  | |    | |/ ____ \ _| |_| |____ ;;
;; |_|    |_|  \_\\____/ \_____|_|  \_\/_/    \_\_|  |_|    |_/_/    \_\_____|______|;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
segment tail align=16
_program_end:
    ; this is just used to fill the parts not in the alignment with 0
    times 16 db 0
