# DOCUMENTATION
Documentation is for compiling, running and debugging ringOS.

[SYSTEM REQUIRATMENS](https://github.com/ringwormGO-organization/ringOS#system-requiratmens)

# Compile and run in Qemu (betas)
[You can use this script (Linux, run in Qemu)](https://github.com/Andrej123456789/ringOS/blob/main/ringOS-Builder-full.sh)

[Stable release (Linux, run in Qemu)](https://github.com/ringwormGO-organization/ringOS/blob/main-and-beta-things/ringOS-stable-Builder.sh)
or continue manually.

### Software you need
1. [Qemu recommended](#install-qemu) or [Virtual Box, VmWare](#running-in-virtual-box-or-vmware)
2. WSL or Linux (recommended)

### Type of release for running in Qemu
Download zip file of Qemu release (example: https://github.com/Andrej123456789/ringOS/releases/tag/Beta11_Qemu).

Otherwise, you can download some branches, [stable release](https://github.com/ringwormGO-organization/ringOS/tree/ringOS-stable1) or clone entire repo and found files which you need.

### Compiling
Unzip zip file and navigate folder to your Terminal (Linux) or WSL on Windows (`cd`).

This commands is for Linux based distros and WSL.

If you first time running WSL or Linux installation, follow these steps:

`sudo apt update`

`sudo apt-get install build-essential mtools`

`sudo apt install nasm`

`sudo apt-get install lld`
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

# Compile and run stable release

[Shell scipt](https://github.com/ringwormGO-organization/ringOS/blob/main-and-beta-things/ringOS-stable-Builder.sh)

[Manually download binary](https://github.com/ringwormGO-organization/ringOS/releases/tag/ringOSv1)

______
# Install Qemu

**Windows** Download executable file, run it (https://www.qemu.org/download/#windows) and add Qemu to PATH

**Linux** `sudo apt install qemu-system-x86`
___
# Running in Virtual Box or VMWare

**Minimum RAM: 4096MB**

You need install two more apps:

`sudo apt-get install xorriso`

`sudo apt-get install mkisofs`

Enter kernel/bin directory.

Type this commands in order:

`mkdir -p iso`

`rm -rf iso/*.iso`

`rm -rf iso/*.img`

`cp ringOS.img iso`

`xorriso -as mkisofs -R -f -e ringOS.img -no-emul-boot -o ./iso/ringOS.iso iso`

Open Virtual Box, create new virtual machine and put ISO as CD-ROM device and enable ICH9 CPU chipset.

Open VMWare, create new virtual machine, put ISO, enter Boot Manager and select **EFI Internal Shell**.

![image](https://user-images.githubusercontent.com/83548580/143719557-aee05602-e163-4693-a124-2307aa09eac0.png)

![image](https://user-images.githubusercontent.com/83548580/143719800-0600b9fe-8ca7-48bd-bd24-edc6c3048d56.png)

- - - - - - 

![image](https://user-images.githubusercontent.com/83548580/140312483-09db7765-e788-41d1-b005-c47cb27cb57e.png)

![image](https://user-images.githubusercontent.com/83548580/143719473-982e21ff-def5-4383-aa4f-3b249eab4e90.png)

(You can execute this commands in WSL and run Virtual Box on Windows)

Operating system must be marked as EFI (Virtual box) or UEFI Firmware type (VMWare).
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
# Debug
We have [debug branch](https://github.com/ringwormGO-organization/ringOS/tree/Debug) but code is not updated and is only for Windows platform.

If you want debug new code follow these steps:

Download code, install gdb (```sudo apt-get install gdb```), open Visual Studio Code and create two JSON files.

[Code](https://www.youtube.com/watch?v=XLw_K4rEl1I)

Click F5 to run.
______
# Modules
[Modules](https://github.com/ringwormGO-organization/ringOS/blob/main-and-beta-things/ringOS-Beta17/Modules.txt) are for customizing ringOS.

You can currently personalize by [official modules](https://github.com/ringwormGO-organization/ringOS/blob/main-and-beta-things/ringOS-Beta17/Modules.txt) printing text in kernel.cpp.

Fell free to customize some other parts like panic.cpp

### License for modules
USE THIS MODULES FOR PRIVATE USE

IF YOU PLANNING USE THIS MODULES TO MODIFICATE ringOS AND PUBLISH ringOS PLEASE ASK ringwormGO FOR PERMISSION
___

# Other

If you have problem or idea create **issue**.

For contributiing create **Pull Request**.

This documentation will continue improving based on new features in ringOS.

[ringOSY documentation](https://github.com/ringwormGO-organization/ringOS/tree/ringOSY) 
____

Thank you for choosing ringOS

©ringwormGO 2021
