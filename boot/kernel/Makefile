# $@  target file
# $<  first dependency
# $^  all dependencies
all: run

kernel.bin: kernel_entry.o kernel.o
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary
# specify to the linker that text section is at 0x1000

kernel_entry.o: kernel_entry.asm
	nasm $< -f elf -o $@

kernel.o: kernel.c
	i386-elf-gcc -O2 -nostdlib -nostartfiles -ffreestanding -c $< -o $@

dump: kernel_entry.o kernel.o
	i386-elf-objdump -d $^

kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

bootsect.bin: bootsect.asm
	nasm $< -f bin -o $@

# bootsector and kernel come immediately after each other
kimage.bin: bootsect.bin kernel.bin
	cat $^ > $@

run: kimage.bin
	qemu-system-i386 -fda $<

clean:
	rm *.bin *.o *.dis

