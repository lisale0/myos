CFLAGS = -g
CC = i686-elf-gcc
AS = nasm

all: boot kernel linker bootimage

debug: boot kernel linkerdebug bootimage

boot:
	$(AS) -felf32 boot.asm -o boot.o

kernel:
	$(CC) -g  -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

linker:
	$(CC) -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

linkerdebug:
	$(CC) -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc $(CFLAGS)

verifyboot:
	if grub-file --is-x86-multiboot myos.bin; then \
		echo "multiboot confirmed"; \
	else \
		echo "not multiboot"; \
	fi; \


bootimage:
	mkdir -p isodir/boot/grub
	cp myos.bin isodir/boot/myos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir


qemucd:
	qemu-system-i386 -cdrom myos.iso

qemumulti:
	qemu-system-i386 -kernel myos.bin

qemudebug:
	qemu-system-i386 -machine q35 -kernel myos.bin -gdb tcp::26000 -S 

clean:
	rm boot.o
	rm kernel.o
	rm myos.bin
	rm -rf isodir
