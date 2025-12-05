ASM = nasm
CC = gcc
LD = ld
GRUBMK = grub-mkrescue

ASFLAGS = -f elf32
CFLAGS  = -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector -Iinclude
LDFLAGS = -m elf_i386 -T link.ld

OBJS = \
boot/boot.o \
kernel/kernel_entry.o \
kernel/kernel.o \
kernel/interrupts.o \
kernel/interrupt_handlers.o \
kernel/interrupt_asm.o \
kernel/pic.o \
kernel/keyboard.o \
kernel/fb.o \
kernel/input_buffer.o \
kernel/terminal.o

all: os.iso

boot/boot.o: boot/boot.s
	$(ASM) $(ASFLAGS) boot/boot.s -o boot/boot.o

# C source files
kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Assembly source files
kernel/%.o: kernel/%.s
	$(ASM) $(ASFLAGS) $< -o $@

# Link kernel
kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o kernel.elf $(OBJS)

# Create bootable ISO
os.iso: kernel.elf
	rm -rf iso
	mkdir -p iso/boot/grub
	cp kernel.elf iso/boot/kernel.elf
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo 'menuentry "MyOS" { multiboot /boot/kernel.elf }' >> iso/boot/grub/grub.cfg
	$(GRUBMK) -o os.iso iso

# Run in QEMU
run: os.iso
	qemu-system-i386 -m 64 -cdrom os.iso -display curses

clean:
	rm -rf *.o *.elf os.iso iso boot/*.o kernel/*.o
