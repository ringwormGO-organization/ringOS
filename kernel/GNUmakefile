CC              = cc
CFLAGS          = -O2 -g -Wall -Wextra -Wpedantic
LDFLAGS         =
LD              = ld
QEMU            = qemu-system-x86_64
QEMUFLAGS       = -m 1G -enable-kvm -cpu host

INTERNALLDFLAGS :=         \
	-Tlinker.ld            \
	-nostdlib              \
	-zmax-page-size=0x1000 \
	-static                \
	-pie                   \
	--no-dynamic-linker    \
	-ztext

INTERNALCFLAGS  :=       \
	-I../stivale         \
	-I.                  \
	-I..                 \
	-std=c11             \
	-ffreestanding       \
	-fno-stack-protector \
	-fpie                \
	-mabi=sysv           \
	-mno-80387           \
	-mno-mmx             \
	-mno-3dnow           \
	-mno-sse             \
	-mno-sse2            \
	-mno-red-zone

all: kernel.elf

kernel.elf: kernel.o e9print.o
	$(LD) $^ $(LDFLAGS) $(INTERNALLDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@

%.o: %.asm
	nasm -felf32 $< -o $@

clean:
	rm -rf kernel.elf kernel.o e9print.o