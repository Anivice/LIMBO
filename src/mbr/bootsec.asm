[bits 16]
[org 0x7C00]

SYS_STARTINGPOINT equ 0x7C00

jmp start

print_msg: ;print_msg(ds:dp=null terminated msg)
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

read_disk:  ; read_disk(al=sector_count,ah=starting_sector) ==> es:di
    pusha
    mov             bx,                     ax      ; save ax parameter to bx
    push            bx
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

    jc              disk_error

    pop             bx
    popa
    ret

disk_error:
    pop             bx
    xor             cx,                     cx
    mov             ds,                     cx
    mov             bp,                     .disk_error_msg
    call            print_msg
    mov             ax,                     bx
    and             ax,                     0x00FF
    call            print_num
    mov             bp,                     .disk_err_msg_pt2
    call            print_msg
    and             ax,                     bx
    and             ax,                     0xFF00
    call            print_num
    mov             bp,                     .disk_err_msg_pt3
    call            print_msg
    hlt
    jmp $

.disk_error_msg:
    db "[FDA]: Read error (sec:", 0x00
.disk_err_msg_pt2:
    db ", cnt:", 0x00
.disk_err_msg_pt3:
    db ")", 0x0D, 0x0A, 0x00

    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
start:
    xor             cx,                     cx
    mov             ds,                     cx

    ; print info
    mov             bp,                     _message_mbr_loader
    call            print_msg

    mov             ax,                     0x07C0
    mov             es,                     ax
    mov             di,                     _buffer - SYS_STARTINGPOINT

    mov             ah,                     2                               ; second sector
    mov             al,                     1                               ; read one sector
    call            read_disk

    ; now, we determine how large the program is:
    mov             ax,                     [es:di]                         ; first value is the actual program size
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
    cmp             al,                     0                               ; compare number of the pending sector to read to 0
    je              .end_read                                               ; we have no sector to read, skip (program size < 512 B)
    call            read_disk                                               ; if we still have sectors to read, continuing on
    .end_read:

    mov             bp,                     _done
    call            print_msg

    ; we have already read the whole program, now we need to reset our buffer offset
    mov             di,                     _buffer - SYS_STARTINGPOINT

    ; Now, we relocate the user program. The allocation is hardcoded for simplicity
    ; new_seg_addr = cur_seg + (cur_index + off_in_prog) >> 4

    ; set stack segmentation
    mov word        ax,                     [es:di + 12]                    ; stack segmentation starting address
    add             ax,                     di
    shr             ax,                     4
    add             ax,                     0x07C0
    mov             cx,                     ax

    mov word        ax,                     [es:di + 12]                    ; stack segmentation starting address
    mov word        bx,                     [es:di + 14]                    ; stack segmentation end address
    sub             bx,                     ax
    ; stack protection procedure in case of an interruption
    mov             ss,                     cx
    mov             sp,                     bx

    ; set up data segmentation
    mov word        ax,                     [es:di + 4]                     ; data segmentation starting address
    add             ax,                     di
    shr             ax,                     4
    add             ax,                     0x07C0
    mov             ds,                     ax
    xor             si,                     si

    ; attempt to call _entry_point() with correct code segment (offset starts with 0x0000)
    mov             bx,                     [es:di + 2]                     ; get entry point offset
    mov             ax,                     [es:di + 8]                     ; get code segmentation starting address
    add             ax,                     _buffer                         ; pending the current buffer segment
    shr             ax,                     4                               ; they are all flat address, so we shift 4 bits to the right

    ; Now we clear es to 0, so that we can access our own data section.
    ; with ds now point to the program's own data section, our default
    ; data addressing is now invalid! Luckily, MBR code position is known
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

    ; The loaded program will return to here after it's done with it's designed job
    ; thus, we have to halt the system in case that the processor wonders off
_infinite_loop:
    hlt
    jmp _infinite_loop

_message_mbr_loader:
    db "Stage 1 loader is now reading stage 2 loader...", 0x00

_info_program_size:
    db "size ", 0x00

_endl:
    db " bytes...", 0x00

_done:
    db "done!", 0x0D, 0x0A, 0x00

_far_call:
    dw 0, 0

; What does this do and why it's here? good question. This thing does one job, ensure alignment of _buffer without
; having to setup a separate code segmentation that will messing with the code size
times 16 - (($ - $$) % 16) db 0

_buffer:

times 510 - ($ - $$) db 0
; Boot signature
dw 0xAA55