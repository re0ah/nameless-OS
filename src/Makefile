AS = nasm
CC = gcc

INCLUDE_DIR = ../include/
SRC_DIR = src/

CFLAGS = -m32 -nostdlib -mgeneral-regs-only -nostdinc -fno-builtin -fno-stack-protector \
		 -nostartfiles -nodefaultlibs -Wall -Wextra -c \
		 -I$(INCLUDE_DIR)
LDFLAGS = -T link.ld -melf_i386
ASFLAGS = -f elf

OBJECTS = loader.o kernel.o ports/ports.o stdlib/string/string.o tty/tty.o gdt/gdt.o idt/idt.o pit/pit.o keyboard/keyboard.o pmm/pmm.o mm/mm.o

all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
				-b boot/grub/stage2_eltorito    \
				-no-emul-boot                   \
				-boot-load-size 4               \
				-A os                           \
				-input-charset utf8             \
				-quiet                          \
				-boot-info-table                \
				-o os.iso                       \
				iso

run: os.iso
	qemu-system-i386 -cdrom os.iso

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm *.o kernel.elf os.iso 
	rm gdt/*.o
	rm idt/*.o
	rm stdlib/string/*.o
	rm mm/*.o
	rm keyboard/*.o
	rm pmm/*.o
	rm pit/*.o
	rm ports/*.o
