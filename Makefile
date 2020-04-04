
CROSS_PATH = ~/proj/i686-elf-tools/bin
AS = $(CROSS_PATH)/i686-elf-as
CC = $(CROSS_PATH)/i686-elf-gcc

OUT = build

INCLUDE_DIR = include

TARGET = kernel.elf

LDFLAGS = -T linker.ld -ffreestanding -nostdlib -lgcc
CCFLAGS = -std=gnu99 -ffreestanding -Wall -Wextra -I $(INCLUDE_DIR) -g

OBJ = asm/boot.o tty/strlen.c tty/tty.c kernel/kernel.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<


%.o: %.S
	$(AS) -o $@ $<

run:
	qemu-system-i386 -kernel $(TARGET)

check-multiboot: $(TARGET)
	grub-file --is-x86-multiboot $(TARGET)

clean:
	rm -rf $(TARGET)
	rm -rf asm/*.o
	rm -rf tty/*.o
	rm -rf kernel/*.o
