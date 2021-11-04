# DOCUMENTATION
Documentation is for compiling and running ringOS.

# Compile and run in Qemu
You can use this script (Linux, run in Qemu): https://github.com/Andrej123456789/ringOS/blob/main/ringOS-Builder-full.sh, https://github.com/Andrej123456789/ringOS/releases/tag/AutomaticBuildTool
or continue manually.

### Software you need
1. [Qemu recommended](#install-qemu) or [Virtual Box](#running-in-virtual-box)
2. WSL or Linux (recommended)

### Type of release for running in Qemu
Download zip fileof Qemu release (example: https://github.com/Andrej123456789/ringOS/releases/tag/Beta11_Qemu).

### Compiling
Unzip zip file and navigate folder to your Terminal (Linux) or WSL on Windows (`cd`).

This commands is for Linux based distros and WSL.

If you first time running WSL or Linux installation, follow these steps:

`sudo apt update`

`sudo apt-get install build-essential mtools`

`sudo apt install nasm`
___________________________________________________________________

For compiling bootloader,

`cd gnu-efi`

`make bootloader`

________________________________________________________________

For compiling kernel,

`cd kernel` or (if you are in gnu-efi folder) `cd ../kernel`

`make kernel`

______________________________________________________________

For running image,

`make buildimg` [kernel folder]

**Windows** run `run2.bat` file

**Linux** `make run`


# Install Qemu

**Windows** Download executable file, run it (https://www.qemu.org/download/#windows) and add Qemu to PATH

**Linux** `sudo apt install qemu-system-x86`
___
# Running in Virtual Box
You need install two more apps:

`sudo apt-get install xorriso`

`sudo apt-get install mkisofs`

Enter kernel/bin directory.

Type this commands in order:

`mkdir -p iso`

`rm -rf iso/*.iso`

`rm -rf iso/*.img`

`cp CustomOS.img iso`

`xorriso -as mkisofs -R -f -e CustomOS.img -no-emul-boot -o ./iso/cdimage.iso iso`

Open Virtual Box, create new virtual machine and put ISO as CD-ROM device.

![image](https://user-images.githubusercontent.com/83548580/140312483-09db7765-e788-41d1-b005-c47cb27cb57e.png)

(You can execute this commands in WSL and run Virtual Box on Windows)

Operating system must be marked as EFI.
_____
# Running on real hardware
*Files in [version] - image*

Format USB as MBR/GPT partition style (tool for example: Rufus).

Create EFI folder.

Inside EFI folder create BOOT folder.

Copy `bootx64.efi` file into BOOT folder.

In root directory of USB copy `kernel.elf` and `zap-light16.psf`.

Restart computer, enter Boot Menu and boot from USB.
___

# Modules
[Modules](https://github.com/Andrej123456789/ringOS/blob/main/UEFI%20version/kernel/Info.txt) are for customizing ringOS.

You can currently personalize by [official modules printing](https://github.com/Andrej123456789/ringOS/blob/main/UEFI%20version/kernel/Info.txt) text in kernel.cpp.

Fell free to customize some other parts like panic.cpp

### License for modules
USE THIS MODULES FOR PRIVATE USE
IF YOU PLANNING USE THIS MODULES TO MODIFICATE ringOS AND PUBLISH ringOS PLEASE ASK ringwormGO FOR PERMISSION
___

# Other

If you have problem or idea create **issue**.

For contributiing create **Pull Request**.

This documentation will continue improving based on new features in ringOS.

For ringOSY documentation visit: https://github.com/Andrej123456789/ringOS/blob/Beta11_Qemu/ringOSY/README.md
____

Thank you for choosing ringOS

©ringwormGO 2021
