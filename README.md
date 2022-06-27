# ringOS
ringOS source code

Documentation (will be added later)

[Folder where are shell scripts to install all dependencies and download ringOS](https://github.com/ringwormGO-organization/ringOS/tree/main/install-scripts)

[Latest stable release](https://github.com/ringwormGO-organization/ringOS/releases/tag/ringOSv2.0.0)

[Latest beta release (2.5.0)](https://github.com/ringwormGO-organization/ringOS/releases/tag/v2.5.0)

#### Stable releases
[**ringOS v1.0.0**](https://github.com/ringwormGO-organization/ringOS/releases/tag/ringOSv1)

[**Latest ringOS stable release**](https://github.com/ringwormGO-organization/ringOS/releases/tag/ringOSv2.0.0)

#### Contributing and issues
If you have problem or idea create an **issue**.

If you want contribute to this project create a **Pull Request**.

## About ringOS
ringOS is ringwormGO operating system based on PonchoOS. Limine bootloader and Limine boot protocol are added in May and we are kind of starting again.

ringOS have GUI and we are working on more keyboard support.

This repo is for active development and invitation of new contributors to this project.

![image](https://user-images.githubusercontent.com/83548580/133824416-455bc2d8-3364-4ffd-abd6-24bff779af32.png)
Beta 4 version image of ringOS

![ringOSBeta16](https://user-images.githubusercontent.com/83548580/142688916-7d1e3b52-946d-441e-acf1-137eb4c534c3.png)
Beta16 version image of ringOS

![image](https://user-images.githubusercontent.com/83548580/169691987-e57a476b-5cfb-4d2d-a064-e0f38abc50cb.png)
Image of Limine (main) version of ringOS

### Notes
1. If you want to change the background you have to configure `limine.cfg` *(still beats MS-Win 7+ when it comes to customization)*

## gnu-efi version status
Check old version of README on main branch.

## Checklist
### Bootloaders
- [x] gnu-efi (before)
- [x] [Limine](https://github.com/ringwormGO-organization/ringOS/tree/Limine_dev) (in development, main version)
- [ ] [POSIX](https://github.com/ringwormGO-organization/ringOS/tree/POSIX) (it will be still here)

### Framebuffer info and printing to the screen
- [x] Framebuffer info
- [x] Printing to the screen
- [ ] [printf](#external-dependencies)
- [x] ```\n``` implementaion

### Memory
- [x] Memory info from Limine
- [ ] Bitmap
- [ ] Paging
- [ ] ```malloc``` and ```free```

### Interrupts and IO
- [x] GDT
- [x] IDT
- [ ] Exceptions
- [ ] Panic screen
- [ ] IO
- [ ] Keyboard
- [ ] Mouse

### Virtual Machine supprot
- [ ] VMWare Tools
- [ ] Virtual Box Additions

### File systems
- [ ] VFS
- [ ] DEVFS
- [ ] FAT32
- [ ] ISO9660
- [ ] Ext2
- [ ] Ext4
- [ ] NTFS

### Storage
- [ ] Read
- [ ] Write
- [ ] SATA
- [ ] IDE
- [ ] NVMe

### Timers
- [ ] PIT
- [ ] RTC

### Shell
- [ ] Shell

### GUI - Windowing system
- [ ] Basic framebuffer windowing-system
- [ ] Advanced framebuffer windowing-system (GUI library, GUI API)
- [x] BMP images
- [ ] TGA images
- [ ] Put GUI as process
- [ ] GUI support in User Mode
- [ ] [Own scripting language for GUI](#porting-stuff)

#### Default applications
- [ ] Calculator (maximum number of number1 and number2 is 9)

### User Mode
- [ ] Ring3
- [ ] Loading executables
- [ ] TSS
- [ ] ELF
- [ ] syscall
- [ ] Threads - one or more of them
- [ ] Task Manager - GUI version
- [ ] Task Manager - non GUI version
- [ ] Users - one or more of them

### Porting stuff
- [ ] Python
- [ ] Lua
- [ ] GCC and G++ compiler

#### Lua
- [ ] All functions
- [ ] Lua hello world
- [ ] GUI library

### Other
- [ ] ACPI
- [ ] AHCI
- [ ] Audio
- [ ] Book
- [ ] Installation
- [ ] Networking
- [x] Own build tool (shell scripts, also count for gnu-efi)
- [ ] Real hardware support
- [ ] Use Rust to build ringOS
- [ ] PCI
- [ ] PCIe
- [x] SMBIOS
- [ ] USB

# ringOSY
[ringOSY](https://github.com/ringwormGO-organization/ringOSY)

## System requiratmens
### Hardware
#### Real hardware
Firmware: x86_64 PC

#### In emulator
Qemu: 2GB recommended

Virtual Box, VMWare: 4096MB RAM recommended, ([check this for more information](https://github.com/ringwormGO-organization/ringOS/blob/main-and-beta-things/Documentation.md#running-in-virtual-box-or-vmware))

*Note: Qemu on Windows requires more processor power than Qemu on Linux/MacOS*

### Software
- build-essential (Debian), base-devel (Arch Linux)
- xorriso
- mtools
- Qemu

*See shell script to install software in root of gnu-efi branch.*

## External dependencies
* [printf](https://github.com/eyalroz/printf) *This is forked repository of [original mpaland's printf](https://github.com/mpaland/printf) and also ringwormGO has done little modification to be compatible with ringOS*
* [scalable-font2](https://gitlab.com/bztsrc/scalable-font2) *Just add font in gnu-efi branch, not in use *

## Resources used:
* [Poncho OSDEV 2](https://www.youtube.com/playlist?list=PLxN4E629pPnJxCQCLy7E0SQY_zuumOVyZ) (gnu-efi version)

* Poncho's Discord server

* [LuftOS](https://github.com/Kyota-exe/LuftOS) (gnu-efi version)

* [ilobilo's kernel](https://github.com/ilobilo/kernel)

* [wiki.osdev.org](https://wiki.osdev.org/Main_Page)

Other
______________________

Thank you for choosing ringOS

© ringwormGO 2022
