
OSNAME = ringOS

GNUEFI = ../gnu-efi
OVMFDIR = ../OVMFbin
LDS = kernel.lld
CC = g++
CC2 = gcc
ASMC = nasm
LD = ld.lld

CPPFLAGS = -ffreestanding -fshort-wchar -mno-red-zone -fno-exceptions -g #-g required for debugging
CFLAGS = -ffreestanding -fshort-wchar -mno-red-zone -fno-exceptions -g #-g required for debugging
ASMFLAGS = 
LDFLAGS = -T $(LDS) -static -Bsymbolic -nostdlib

SRCDIR := src
OBJDIR := lib
BUILDDIR = bin
BOOTEFI := $(GNUEFI)/x86_64/bootloader/main.efi

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.cpp)
CSRC = $(call rwildcard,$(SRCDIR),*.c)    
ASMSRC = $(call rwildcard,$(SRCDIR),*.asm)  
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
OBJS += $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%_c.o, $(CSRC))
OBJS += $(patsubst $(SRCDIR)/%.asm, $(OBJDIR)/%_asm.o, $(ASMSRC))

DIRS = $(wildcard $(SRCDIR)/*)

kernel: $(OBJS) link

$(OBJDIR)/interrupts/interrupts.o: $(SRCDIR)/interrupts/interrupts.cpp
	@ echo !==== COMPILING $^
	@ mkdir -p $(@D)
	$(CC) -mno-red-zone -mgeneral-regs-only -ffreestanding -g -c $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@ echo !==== COMPILING $^
	@ mkdir -p $(@D)
	$(CC) $(CPPFLAGS) -c $^ -o $@

$(OBJDIR)/%_c.o: $(SRCDIR)/%.c
	@ echo !==== COMPILING $^
	@ mkdir -p $(@D)
	$(CC2) $(CFLAGS) -c $^ -o $@

$(OBJDIR)/%_asm.o: $(SRCDIR)/%.asm
	@ echo !==== COMPILING $^
	@ mkdir -p $(@D)
	$(ASMC) $(ASMFLAGS) $^ -f elf64 -o $@
	 
link:
	@ echo !==== LINKING
	$(LD) $(LDFLAGS) -o $(BUILDDIR)/kernel.elf $(OBJS) 

setup:
	@mkdir $(BUILDDIR)
	@mkdir $(SRCDIR)
	@mkdir $(OBJDIR)

buildimg:
	dd if=/dev/zero of=$(BUILDDIR)/$(OSNAME).img bs=512 count=93750
	mformat -i $(BUILDDIR)/$(OSNAME).img -F ::
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BOOTEFI) ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img startup.nsh ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/kernel.elf ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/zap-light16.psf ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/Test.bmp ::

run:
	qemu-system-x86_64 -machine q35 -drive file=$(BUILDDIR)/$(OSNAME).img -m 3G -cpu qemu64 -drive if=pflash,format=raw,unit=0,file="$(OVMFDIR)/OVMF_CODE-pure-efi.fd",readonly=on -drive if=pflash,format=raw,unit=1,file="$(OVMFDIR)/OVMF_VARS-pure-efi.fd" -net none
clean:
	rm -rf lib