# ringOS Documentation
This documentation is intended to guide you in developing, compiling, debugging and running ringOS

[SYSTEM REQUIREMENTS](https://github.com/ringwormGO-organization/ringOS#system-requiratmens)

## Compile and run in Qemu (betas)
[You can use this script (Linux, run in Qemu)](https://github.com/Andrej123456789/ringOS/blob/main/ringOS-Builder-full.sh)

[Stable release (Linux, run in Qemu)](https://github.com/ringwormGO-organization/ringOS/blob/main-and-beta-things/ringOS-stable-Builder.sh)
or continue manually.

### Software you need
1. [Qemu recommended](#install-qemu) or [Virtual Box, VmWare](#running-in-virtual-box-or-vmware)
2. WSL/WSL2 (If developing on Windows) or Linux (recommended)

### Type of release for running in Qemu
Download a Zip file of Qemu release (example: https://github.com/Andrej123456789/ringOS/releases/tag/Beta11_Qemu).

Unzip the downloaded Zip folder and navigate to the contents in your Terminal (Linux) or using WSL/WSL2 on Windows ('cd')

--------------------------------------------------------------------------------------------------------------------------------
For compiling Beta version.

`git clone https://github.com/VanGutan/gnu-efi` 

Create one ringOS folder, clone `gnu-efi`, `ringOS-beta17` rename as `kernel` and clone `git clone https://github.com/VanGutan/ringOS-Beta14-OVMFTemplate` and rename as `OVMFbin`.
Copy `ringOS-Beta17-bootloader` folder into `gnu-efi` folder and rename it to `bootloader`.

For cloning bootloader, you can [Makefile](https://github.com/ringwormGO-organization/ringOS/blob/main/Makefile)

### Compiling
The following commands work on Debian-based (ex. Ubuntu) Linux distros and within WSL/WSL2 on Windows. Users of non-Debian distros will need to locate the correct packages for their chosen operating system.

If this is your first time attemtping to to compile ringOS, you will need to run the following commands in your Terminal (Linux) or using WSL/WSL2 on Windows:

`sudo apt update`

`sudo apt-get install build-essential mtools`

`sudo apt install nasm`

`sudo apt-get install lld`
___________________________________________________________________

To compile the bootloader (gnu-efi) you will need to run the following commands in your Terminal (Linux) or using WSL/WSL2 on Windows:

`cd gnu-efi`

`make bootloader`

________________________________________________________________

To compile the ringOS kernel you will need to run the following commands in your Terminal (Linux) or using WSL/WSL2 on Windows:

`cd kernel` or (if you are in gnu-efi folder) `cd ../kernel`

`make kernel`

______________________________________________________________

To run ringOS within Qemu on Linux or Windows:

**Windows** double-click the  `run2.bat` file to initialize a Qemu VM and run ringOS.

**Linux** `make buildimg` [run from with the 'kernel' folder]

**Linux** `make run`

# Compile and run the latest stable release from shell script

[Shell scipt](https://github.com/ringwormGO-organization/ringOS/blob/main-and-beta-things/ringOS-stable-Builder.sh)

[Manually download binary](https://github.com/ringwormGO-organization/ringOS/releases/tag/ringOSv1)

______

## Install Qemu

**Windows** Download executable file, run it (https://www.qemu.org/download/#windows) and add Qemu to PATH

**Linux** `sudo apt install qemu-system-x86`
___
## Running in Virtual Box or VMWare

**Minimum RAM: 4096MB**

You need install two more apps:

`sudo apt-get install xorriso`

`sudo apt-get install mkisofs`

Enter kernel/bin directory.

Type these commands in order:

`mkdir -p iso`

`rm -rf iso/*.iso`

`rm -rf iso/*.img`

`cp ringOS.img iso`

`xorriso -as mkisofs -R -f -e ringOS.img -no-emul-boot -o ./iso/ringOS.iso iso`

Open Virtual Box, create new virtual machine and put ISO as CD-ROM device and enable ICH9 CPU chipset.

Open VMWare, create new virtual machine, put ISO, enter Boot Manager by pressing **ESC** during boot and select **EFI Internal Shell**.

![image](https://user-images.githubusercontent.com/83548580/143719557-aee05602-e163-4693-a124-2307aa09eac0.png)

![image](https://user-images.githubusercontent.com/83548580/143719800-0600b9fe-8ca7-48bd-bd24-edc6c3048d56.png)

- - - - - - 

![image](https://user-images.githubusercontent.com/83548580/149768519-9a16bc9d-dd7e-4e29-8941-86f9733e19f0.png)

![image](https://user-images.githubusercontent.com/83548580/143719473-982e21ff-def5-4383-aa4f-3b249eab4e90.png)

(You can execute this commands in WSL and run Virtual Box on Windows)

Operating system must be marked as EFI (Virtual box) or UEFI Firmware type (VMWare).
_____
## Running on real hardware
*Files in [version] - image*

Format USB as MBR/GPT partition style (tool for example: Rufus).

Create EFI folder.

Inside EFI folder create BOOT folder.

Copy `bootx64.efi` file into BOOT folder.

In root directory of USB copy `kernel.elf`, `zap-light16.psf` and `Picture.bmp` files.

Restart computer, enter UEFI Menu and boot from USB.
___
## Debug
We have a [debug branch](https://github.com/ringwormGO-organization/ringOS/tree/Debug) but the code is not updated and is only for Windows platform developers.

If you want to debug new code follow these steps:

Download code to be debugged, install gdb (```sudo apt-get install gdb```), open Visual Studio Code and create two JSON files.

[Code](https://www.youtube.com/watch?v=XLw_K4rEl1I)

Click F5 to run.
______
## Modules
[Modules](https://github.com/ringwormGO-organization/ringOS/blob/main-and-beta-things/ringOS-Beta17/Modules.txt) are for customizing ringOS.

You can currently personalize the operating system output by using the provided [official modules](https://github.com/ringwormGO-organization/ringOS/blob/main-and-beta-things/ringOS-Beta17/Modules.txt)  and printing text in kernel.cpp.

Feel free to customize some other parts like panic.cpp as appropriate for your use case.

### License for modules
The modules provided for customization are intended for private, non-commerical use only.

IF YOU PLANNING USE THESE MODULES TO MODIFY ringOS AND PUBLISH ringOS AS YOUR OWN DISTRIBUTION, PERMISSION MUST FIRST BE OBTAINED FROM ringwormGO.
___

## Other

If you have problems or ideas plese create an **issue**.

To contribute to ringOS, please create a **Pull Request** and refer to [our coding sytle](https://github.com/ringwormGO-organization/ringOS/blob/main/CONTRIBUTING.md#coding-sytle-for-pull-requests) down below.

This documentation will continue improving based on new features in ringOS.

[ringOSY documentation](https://github.com/ringwormGO-organization/ringOS/tree/ringOSY) 
________________________________________________________________________________________________________________________________________________

Thank you for choosing ringOS and ringOSY

©ringwormGO 2022
