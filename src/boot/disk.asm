disk_load_second_stage:

        mov ah, 02h ;int 13h function for read disk
        mov al, 4
        mov dl, dl
        ;read 4 sector
        mov cl, 0x02
        mov ch, 0
        mov dh, 0

        mov bx, 0x7e00

        int 13h
        jc disk_error
        ret

disk_load_kernel:
        mov ah, 02h

        mov al, 20
        mov dl, dl

        mov cl, 0x06
        mov ch, 0
        mov dh, 0

        mov bx, 0x8600
        int 13h
        jc disk_error
        ret

disk_error:
        lea bx, [disk_error_message]
        call bios_print
        call bios_println
        jmp $
