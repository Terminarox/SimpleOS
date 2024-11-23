
second_stage_boot_loader:
lea bx, [second_stage_boot_loader_message]
call bios_print
call bios_println

lea bx, [second_stage_load_kernel_message]
call bios_print
call bios_println

call disk_load_kernel
lea bx, [second_stage_kernel_loaded_message]
call bios_print
call bios_println

lea bx, [second_stage_load_gdt_message]
call bios_print
call bios_println

switch_to_pm:
    cli ; 1. disable interrupts
    lgdt [gdt_descriptor] ; 2. load the GDT descriptor
    mov eax, cr0
    or eax, 0x1 ; 3. set 32-bit mode bit in cr0
    mov cr0, eax
    jmp CODE_SEG:init_32
    ret

[bits 32]
init_32:
        jmp 0x8600




; this is how constants are defined
letter: db 'x', 0
second_stage_boot_loader_message: db '16-bits real mod: Stage 2: stage 2 loaded at `0x7E00`.', 0
second_stage_load_kernel_message: db '16-bits real mod: Stage 2: Loading Kernel from disk...', 0
second_stage_load_gdt_message: db '16-bits real mod: Stage 2: Loading GDT...', 0
second_stage_loaded_gdt_message: db '32-bits protected mod: Stage 2: GDT loaded.'
second_stage_kernel_loaded_message: db '16-bits real mod: Stage 2: kernel loaded at `0x8600`.', 0


;protection is used with pagination.
gdt_start:
        dd 0x0
        dd 0x0
code_seg:
        dw 0xffff ;spawn all of the 4Go of memory in 32 bits protected mod.
        ; segment's base
        dw 0x0
        db 0x0
        ;flag -- see osdev.org
        db 10011011b
        db 11001111b

        db 0x0
data_seg:
        dw 0xffff

        dw 0x0
        db 0x0

        db 10010110b
        db 11001111b

        db 0x0
gdt_end:

gdt_descriptor:
        dw gdt_start - gdt_end - 1
        dd gdt_start

CODE_SEG equ code_seg-gdt_start
DATA_SEG equ data_seg-gdt_start


times 2048-($-second_stage_boot_loader) db 0
