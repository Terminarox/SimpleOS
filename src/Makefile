# $@ = target file
# $< = first dependency
# $^ = all dependencies

export PATH := /usr/local/i386elfgcc/bin:$(PATH)

all: clean run

run: build/os.img
	qemu-system-i386 $<

clean:
	rm -rf build/*
build/os.img: build/os.bin
	dd if=$^ of=$@ bs=512 seek=0
build/0.bin: kernel/0.asm
	nasm -f bin $< -o $@


build/boot.bin: boot/boot.asm
	nasm -f bin $< -o $@

build/kernel.o: kernel/kernel.c
	i386-elf-gcc -Wall -Wextra  -nostdlib -ffreestanding -c $< -o $@

build/kernel_entry.o: kernel/kernel_entry.asm
	nasm -f elf $< -o $@

build/kernel.bin: build/kernel_entry.o  build/kernel.o build/kernel_rc.o build/vga.o build/vga_supplement.o build/strings.o build/time.o
		i386-elf-ld -o $@ -Ttext 0x8600 $^ --oformat binary

build/os.bin: build/boot.bin build/kernel.bin build/0.bin
	cat $^ > $@

build/vga.o: kernel/drivers/vga.c
	i386-elf-gcc -Wall -Wextra -nostdlib -Wsuggest-final-types -ffreestanding -c $< -o $@
build/kernel_rc.o: kernel/kernel_rc.c
	i386-elf-gcc -Wall -Wextra -nostdlib -Wsuggest-final-types -ffreestanding -c $< -o $@
build/vga_supplement.o: kernel/drivers/vga_supplement.c
	i386-elf-gcc -Wall -Wextra -nostdlib -Wsuggest-final-types -ffreestanding -c $< -o $@
build/strings.o: kernel/drivers/strings.c
	i386-elf-gcc -Wall -Wextra -nostdlib -Wsuggest-final-types -ffreestanding -c $< -o $@
build/time.o: kernel/drivers/time.c
	i386-elf-gcc -Wall -Wextra -nostdlib -Wsuggest-final-types -ffreestanding -c $< -o $@
