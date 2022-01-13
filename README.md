# ringOS
ringOS source code

[Documentation](https://github.com/Andrej123456789/ringOS/blob/main/Documentation.md)

[Automatic build tool for Linux (run ringOS in Qemu, beta)](https://github.com/Andrej123456789/ringOS/blob/main/ringOS-Builder-full.sh)

[Automatic Build Tool - stable release](https://github.com/ringwormGO-organization/ringOS/releases/tag/ringOSv1)

[Modules](https://github.com/ringwormGO-organization/ringOS/blob/main-and-beta-things/ringOS-Beta17/Modules.txt)

### Stable releases
[**ringOS stable release**](https://github.com/ringwormGO-organization/ringOS/tree/ringOS-stable1)

[**ringOSY stable release**](https://github.com/ringwormGO-organization/ringOS/tree/ringOSY)

### Contributing and issues
If you have problem or idea create an **issue**.

If you want contribute to this project create a **Pull Request**.

# About ringOS
ringOS is ringwormGO operating system based on PonchoOS with support for UEFI boot mode only.

ringOS is keyboard oriented operating system with GUI elements.

This repo is for active development and invitation of new contributors to this project.

![image](https://user-images.githubusercontent.com/83548580/133824416-455bc2d8-3364-4ffd-abd6-24bff779af32.png)
Beta 4 version image of ringOS

![ringOSBeta16](https://user-images.githubusercontent.com/83548580/142688916-7d1e3b52-946d-441e-acf1-137eb4c534c3.png)
Beta16 version image of ringOS

# Checklist
### Bootloaders
- [x] gnu-efi
- [ ] Limine (we left developing Limine)

### Framebuffer info and printing to the screen
- [x] Framebuffer info
- [x] Printing to the screen
- [x] ```\n``` implementaion

### Memory
- [x] Bitmap
- [x] Paging
- [x] ```malloc``` and ```free```

### Interrupts and IO
- [x] GDT
- [x] IDT
- [x] Exceptions
- [x] Panic screen
- [x] IO
- [x] Keyboard
- [x] Mouse

### Virtual Machine supprot
- [ ] VMWare Tools
- [ ] Virtual Box Additions

### File systems
- [ ] VFS
- [ ] DEVFS
- [ ] FAT32
- [ ] NTFS
- [ ] ISO9660
- [ ] Ext2
- [ ] Ext4

### Storage

- [x] SATA
- [ ] IDE
- [ ] NVMe

### Timers
- [x] PIT

### Shell
- [ ] Shell

### GUI - Windowing system
- [x] Framebuffer windowing-system
- [x] BMP images
- [ ] TGA images
- [ ] Own scripting language for GUI

### User Mode
- [ ] Ring3
- [ ] TSS
- [ ] ELF
- [ ] syscall
- [ ] Threads - one or more of them
- [ ] Task Manager
- [ ] Users - one or more of them

### Other
- [x] ACPI
- [x] AHCI
- [ ] Audio
- [ ] Book
- [ ] Networking
- [x] Own build tool
- [ ] Real hardware support
- [x] PCI
- [ ] PCIe
- [ ] USB


# ringOSY
[ringOSY](https://github.com/ringwormGO-organization/ringOSY)

# System requiratmens

### Real hardware
Firmware: UEFI x86_64 PC

RAM: Uncertain, but we recommend 3GB of RAM based on testing 

### In emulator
Qemu: 38MB RAM min, 3GB recommended

Virtual Box, VMWare: 4096MB RAM minimum, ([check this for more information](https://github.com/ringwormGO-organization/ringOS/blob/main-and-beta-things/Documentation.md#running-in-virtual-box-or-vmware))

CPU: minimum - Intel Celeron N3350; recommended - Intel Core i5

*Note: Qemu on Windows requires more processor power than Qemu on Linux/macOS*

# Resources used:
[Poncho OSDEV 2](https://www.youtube.com/playlist?list=PLxN4E629pPnJxCQCLy7E0SQY_zuumOVyZ)

Poncho's Discord server

[LuftOS](https://github.com/Kyota-exe/LuftOS)

[wiki.osdev.org](https://wiki.osdev.org/Main_Page)

Other 
______________________

Thank you for choosing ringOS

© ringwormGO 2021
