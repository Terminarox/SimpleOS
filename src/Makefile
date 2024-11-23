# $@ = target file
# $< = first dependency
# $^ = all dependencies
all: clean build/os.bin run

run:
	qemu-system-i386 build/os.bin

clean:
	rm -rf build/*
build/0.bin: kernel/0.asm
	nasm -f bin $< -o $@


build/boot.bin: boot/boot.asm
	nasm -f bin $< -o $@

build/kernel.o: kernel/kernel.c
	i386-elf-gcc -ffreestanding -c $< -o $@

build/kernel_entry.o: kernel/kernel_entry.asm
	nasm -f elf $< -o $@

build/kernel.bin: build/kernel_entry.o  build/kernel.o
		i386-elf-ld -o $@ -Ttext 0x8600 $^ --oformat binary

build/os.bin: build/boot.bin build/kernel.bin build/0.bin
	cat $^ > $@
