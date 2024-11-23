[org 0x7c00]

; addresse of string
lea bx, [boot_sector_message]
call bios_print
call bios_println
; second stage boot loader will be load at 0x7C00 + 512 bits (at the end of boot sector loaded by bios)
; loading address of second stage boot loader is 0x7E00
lea bx, [load_disk_message]
call bios_print
call bios_println

call disk_load_second_stage
jmp second_stage_boot_loader

bios_print:
        ;pusha

        mov ah, 0eh
        mov al, [bx]
        int 10h

        add bx, 1

        cmp al, 0
        jne bios_print

        ;popa
        ret
bios_println:
        mov ah, 0eh
        mov al, 0xa
        int 10h

        mov al, 0xd
        int 10h

        ret

%include 'boot/disk.asm'
boot_sector_message:
db '16-bits real mod: Stage 1: Boot sector stage 1 loaded at `7C00`.', 0
load_disk_message:
db '16-bits real mod: Stage 1: Loading stage 2 from disk into memory...', 0
disk_error_message:
db '16-bits real mod: Stage 1: Error loading from disk. CF=1.', 0

times 510-($-$$) db 0
dw 0xaa55
%include 'boot/stage2boot.asm'
