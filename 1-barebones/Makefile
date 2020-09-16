all: boot kernel linker bootimage

boot: boot.s
	i686-elf-as boot.s -o boot.o

kernel: kernel.c
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

linker: linker.ld
	i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc


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

clean:
	rm boot.o
	rm kernel.o
	rm myos.bin
	rm -rf isodir
