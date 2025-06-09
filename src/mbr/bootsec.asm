; Boot sector, responsible for loading second stage program (max 17 sectors)

[bits 16]
[org 0x7C00]

SYS_STARTINGPOINT equ 0x7C00

jmp start

print_msg: ;print_msg(ds:bp=null terminated msg)
    pusha
    push            ds
    .print_hello:
        mov         ah,                     0x0E
        mov         al,                     [ds:bp]
        ; check if al is null
        cmp         al,                     0x00
        ; is null, exit
        je          .print_hello_end
        ; not null, print
        int         0x10
        inc         bp
        jmp         .print_hello
    .print_hello_end:
    pop             ds
    popa
    ret

print_num: ;print_num(ax=num)
    pusha
    xor             cx,                     cx
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
        int         0x10
    loop .print

    popa
    ret

read_disk:  ; read_disk(al=sector_count,ah=starting_sector) ==> es:di note: this code supports only 17 sectors at most
    pusha
    mov             bx,                     ax      ; save ax parameter to bx
    mov             ah,                     0x00    ; INT 13h, function 00h = reset
    mov             dl,                     0x00    ; drive 0 = A:
    int             0x13                            ; ignore errors for now

    mov             ah,                     0x02    ; function 02h = read sectors
    mov             al,                     bl      ; AL = how many 512-byte sectors
    mov             ch,                     0x00    ; CH = cylinder 0
    mov             cl,                     bh      ; CL = sector 1
    mov             dh,                     0x00    ; DH = head 0
    mov             dl,                     0x00    ; DL = drive 0 (A:)

    ; buffer: es:bx
    mov             bx,                     di
    int             0x13

    jc              .disk_error

    popa
    ret

.disk_error:
    xor             cx,                     cx
    mov             ds,                     cx
    mov             bp,                     .disk_error_msg
    call            print_msg
    cli
    hlt
    jmp             $

.disk_error_msg: db "[MBR FDA]: Floopy disk read error", 0x00

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
start:
    ; print info
    xor             cx,                     cx                              ; clear cx
    mov             ds,                     cx                              ; use zeroed out'd cx to clear ds, ds is used as ds:bp for print_msg
    mov             bp,                     _message_mbr_loader             ; actual message
    call            print_msg                                               ; print message

    ; read_disk(al=sector_count,ah=starting_sector) ==> es:di
    ; prepare buffer
    mov             ax,                     _buffer                         ; buffer segment base linear
    shr             ax,                     4                               ; convert it to segment address
    mov             es,                     ax                              ; put it into es
    xor             di,                     di                              ; clear out di

    ; read one sector (2) only to check the header
    mov             ah,                     2                               ; second sector
    mov             al,                     1                               ; read one sector
    call            read_disk

    ; now, we determine how large the program is:
    mov             ax,                     [es:di]                         ; first value is the actual program size
    add             ax,                     16                              ; add header size
    ; print info:
    mov             bp,                     _info_program_size
    call            print_msg
    call            print_num
    mov             bp,                     _endl
    call            print_msg
    ; now that ax is the actual program size, we determine how much sectors it occupies
    xor             dx,                     dx
    mov             bx,                     512
    div             bx
    ; we see if dx is zero, if not, we add one more sector to read
    cmp             dx,                     0x00
    je              .skip_add_sector
    ; if the program occupies more data but not a full sector, we have to manually add one more sector to read
    inc             ax
    .skip_add_sector:

    ; since we have already read the second sector, we skip that and move buffer offset to new location
    add             di,                     512
    dec             al
    mov             ah,                     3                               ; read starting from the third sector

    ; we don't proceed if loader is larger than 17 sectors
    cmp             al,                     16
    jle             .continue

    xor             cx,                     cx
    mov             ds,                     cx
    mov             bp,                     _too_large
    call            print_msg

    .@@1: hlt
    jmp .@@1
    .continue:
    cmp             al,                     0                               ; compare number of the pending sector to read to 0
    je              .end_read                                               ; we have no sector to read, skip (program size < 512 B)
    call            read_disk                                               ; if we still have sectors to read, continuing on
    .end_read:

    mov             bp,                     _done
    call            print_msg

    ; we have already read the whole program, now we need to reset our buffer offset
    xor             di,                     di

    ; Now, we relocate the user program. The allocation is hardcoded for simplicity
    ; new_seg_addr = cur_seg + (cur_index + off_in_prog) >> 4

    ; set stack segmentation
    ; get segment base
    mov word        ax,                     [es:di + 12]                    ; stack segmentation starting address
    add             ax,                     _buffer                         ; add segment with base segment
    shr             ax,                     4                               ; convert linear to segment
    mov             cx,                     ax                              ; put stack segment to cx
    ; get segment size
    mov word        ax,                     [es:di + 12]                    ; stack segmentation starting address
    mov word        bx,                     [es:di + 14]                    ; stack segmentation end address
    sub             bx,                     ax                              ; calculate stack size
    ; set segment info
    cli                                                                     ; disable interrupt
    mov             ss,                     cx                              ; set stack segment
    mov             sp,                     bx                              ; set stack size
    sti                                                                     ; enable interrupt

    ; set up data segmentation
    mov word        ax,                     [es:di + 4]                     ; data segmentation starting address
    add             ax,                     _buffer                         ; add segment with base segment
    shr             ax,                     4                               ; convert linear to segment
    mov             ds,                     ax                              ; set data segment
    xor             si,                     si                              ; clear data segment pointer

    ; attempt to call _entry_point() with correct code segment (offset starts with 0x0000)
    mov             bx,                     [es:di + 2]                     ; get entry point offset
    mov             ax,                     [es:di + 8]                     ; get code segment starting address
    add             ax,                     _buffer                         ; pending the current buffer segment
    shr             ax,                     4                               ; convert to segment

    ; Now we clear es to 0, so that we can access our own data section.
    ; with ds now point to the program's own data section, our default
    ; data addressing is now invalid! Luckily, MBR code position is known[MBR ERROR]
    ; so we can override with known values, in this case, the easiest one is
    ; to just use '0x00'
    xor             cx,                     cx
    mov             es,                     cx

    ; to perform a long call, we need to provide both Code Segmentation address for CS, and offset index for IP
    ; Now that call doesn't accept register combination for long call, we use memory instead
    ; the memory map should look like this: offset, segmentation.
    mov             [es:_far_call],         bx                              ; offset
    mov             [es:_far_call+2],       ax                              ; segmentation

    call far        [es:_far_call]

    ; Loader should load kernel and boot, not return to MBR
    cli
halt_system:
    hlt
    jmp             halt_system

_too_large:
    db 0x0D, 0x0A, "[MBR ERROR]: Loader too long, max 17 sectors!", 0x0D, 0x0A, 0x00

_message_mbr_loader:
    db "[MBR INFO]: MBR loader is now reading stage 2 loader...", 0x00

_info_program_size:
    db "size ", 0x00

_endl:
    db " bytes...", 0x00

_done:
    db "done!", 0x0D, 0x0A, 0x00

_far_call:
    dw 0, 0

; buffer is a segment, need to be 16 byte aligned
align 16, db 0
_buffer:

times 510 - ($ - $$) db 0
; Boot signature
dw 0xAA55
