# ringOS
ringOS source code

[Documentation](https://github.com/Andrej123456789/ringOS/blob/main/Documentation.md)

[Shell script for latest stable release](https://github.com/ringwormGO-organization/ringOS/blob/main/ringOS-stable-Builder.sh)

[Latest stable release](https://github.com/ringwormGO-organization/ringOS/releases/tag/ringOSv2.0.0)

[Modules](https://github.com/ringwormGO-organization/ringOS/blob/main-and-beta-things/ringOS-Beta17/Modules.txt)

#### Stable releases
[**ringOS v1.0.0**](https://github.com/ringwormGO-organization/ringOS/releases/tag/ringOSv1)

[**Latest ringOS stable release**](https://github.com/ringwormGO-organization/ringOS/releases/tag/ringOSv2.0.0)

#### Contributing and issues
If you have problem or idea create an **issue**.

If you want contribute to this project create a **Pull Request**.

## About ringOS
ringOS is ringwormGO operating system based on PonchoOS with support for UEFI boot mode only.

ringOS is keyboard oriented operating system with GUI elements.

This repo is for active development and invitation of new contributors to this project.

![image](https://user-images.githubusercontent.com/83548580/133824416-455bc2d8-3364-4ffd-abd6-24bff779af32.png)
Beta 4 version image of ringOS

![ringOSBeta16](https://user-images.githubusercontent.com/83548580/142688916-7d1e3b52-946d-441e-acf1-137eb4c534c3.png)
Beta16 version image of ringOS

## Checklist
#### Bootloaders
- [x] gnu-efi
- [ ] [Limine](https://github.com/ringwormGO-organization/ringOS/tree/Limine_dev) (outside support)
- [ ] [POSIX](https://github.com/ringwormGO-organization/ringOS/tree/POSIX) (still not implement)

#### Framebuffer info and printing to the screen
- [x] Framebuffer info
- [x] Printing to the screen
- [x] [printf](#external-dependencies)
- [x] ```\n``` implementaion

#### Memory
- [x] Bitmap
- [x] Paging
- [x] ```malloc``` and ```free```

#### Interrupts and IO
- [x] GDT
- [x] IDT
- [x] Exceptions
- [x] Panic screen
- [x] IO
- [x] Keyboard
- [x] Mouse

#### Virtual Machine supprot
- [ ] VMWare Tools
- [ ] Virtual Box Additions

#### File systems
- [ ] VFS
- [ ] DEVFS
- [ ] FAT32
- [ ] ISO9660
- [ ] Ext2
- [ ] Ext4
- [ ] NTFS

#### Storage
- [x] Read
- [ ] Write
- [x] SATA
- [ ] IDE
- [ ] NVMe

#### Timers
- [x] PIT
- [ ] RTC

#### Shell
- [ ] Shell

#### GUI - Windowing system
- [x] Basic framebuffer windowing-system
- [ ] Advanced framebuffer windowing-system (GUI library)
- [x] BMP images
- [ ] TGA images
- [ ] Put GUI as process
- [ ] GUI support in User Mode
- [ ] [Own scripting language for GUI](https://github.com/ringwormGO-organization/ringwormGO-Standard-Code)

##### Default applications
- [x] Calculator (maximum number of number1 and number2 is 9)

#### User Mode
- [ ] Ring3
- [ ] TSS
- [ ] ELF
- [ ] syscall
- [ ] Threads - one or more of them
- [ ] Task Manager - GUI version
- [ ] Task Manager - non GUI version
- [ ] Users - one or more of them

#### Porting stuff
- [ ] Python
- [ ] Lua
- [ ] GCC and G++ compiler

#### Other
- [x] ACPI
- [x] AHCI
- [ ] Audio
- [ ] Book
- [ ] Installation
- [ ] Networking
- [x] Own build tool
- [ ] Real hardware support
- [x] PCI
- [ ] PCIe
- [x] SMBIOS
- [ ] USB

# ringOSY
[ringOSY](https://github.com/ringwormGO-organization/ringOSY)

## System requiratmens
### Hardware
#### Real hardware
Firmware: UEFI x86_64 PC

RAM: 3GB is the **MAXIMUM** 

#### In emulator
Qemu: 38MB RAM min, 3GB recommended

Virtual Box, VMWare: 4096MB RAM minimum, ([check this for more information](https://github.com/ringwormGO-organization/ringOS/blob/main-and-beta-things/Documentation.md#running-in-virtual-box-or-vmware))

CPU: minimum - Intel Celeron N3350; recommended - Intel Core i5

*Note: Qemu on Windows requires more processor power than Qemu on Linux/MacOS*

### Software
- build-essential
- mtools
- lld
- Qemu

*See shell script to install software.*

## External dependencies
* [printf](https://github.com/eyalroz/printf) *This is forked repository of [original mpaland's printf](https://github.com/mpaland/printf) and also ringwormGO has done little modification to be compatible with ringOS*

## Resources used:
* [Poncho OSDEV 2](https://www.youtube.com/playlist?list=PLxN4E629pPnJxCQCLy7E0SQY_zuumOVyZ)

* Poncho's Discord server

* [LuftOS](https://github.com/Kyota-exe/LuftOS)

* [ilobilo's kernel](https://github.com/ilobilo/kernel)

* [wiki.osdev.org](https://wiki.osdev.org/Main_Page)

Other
______________________

Thank you for choosing ringOS

© ringwormGO 2022
