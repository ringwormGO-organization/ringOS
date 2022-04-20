# ringOS Documentation
This documentation is intended to guide you in developing, compiling, debugging and running ringOS

[SYSTEM REQUIREMENTS](https://github.com/ringwormGO-organization/ringOS#system-requiratmens)

## Compile and run in Qemu (betas)
[You can use this script (Linux, run in Qemu)](https://github.com/ringwormGO-organization/ringOS/blob/main/ringOS-beta.sh)

### Software you need
1. [Qemu recommended](#install-qemu) or [Virtual Box, VMWare Workstation](#running-in-virtual-box-or-vmware)
2. WSL/WSL2 (If developing on Windows) or Linux (recommended)

### Type of release for running in Qemu
Download a Zip file of Qemu release (example: https://github.com/Andrej123456789/ringOS/releases/tag/Beta11_Qemu).

Unzip the downloaded Zip folder and navigate to the contents in your Terminal (Linux) or using WSL/WSL2 on Windows ('cd')

Support for Red Hat(-based) Linux distribution just come, if you want to improve consider become a contributor.

--------------------------------------------------------------------------------------------------------------------------------
### Compile beta version from shell script
#### How to run shell script for Debian based Linux distros:
`./ringOS-beta.sh`

This shell script will also install everything you need; if you have everything installed use `compile.sh`.

### Compiling
The following commands work on Debian-based (ex. Ubuntu) Linux distros and within WSL/WSL2 on Windows. Users of non-Debian distros will need to locate the correct packages for their chosen operating system.

If this is your first time attemtping to to compile ringOS, you will need to run the following commands in your Terminal (Linux) or using WSL/WSL2 on Windows:

`sudo apt-get update`

`sudo apt-get install build-essential mtools`

`sudo apt-get install nasm`

`sudo apt-get install lld`

Packages for Red Hat(-based) distros (NOT TESTED YET!!!):
`sudo yum check-update`

`sudo yum group install "Development tools"`

`sudo subscription-manager repos --enable codeready-builder-for-rhel-8-x86_64-rpms` for Red Hat Enterprise Linux

`sudo yum install nasm`

`sudo yum install qemu-kvm`

`sudo yum install git`

`sudo yum install lld`

`sudo yum install xorriso`

`sudo yum install mkisofs`
___________________________________________________________________

To compile the bootloader (gnu-efi) you will need to run the following commands in your Terminal (Linux) or using WSL/WSL2 on Windows:

`cd gnu-efi`

`make bootloader`

________________________________________________________________

To compile the ringOS kernel you will need to run the following commands in your Terminal (Linux) or using WSL/WSL2 on Windows:

`cd kernel` or (if you are in gnu-efi folder) `cd ../kernel`

`make kernel`

`make buildimg`
______________________________________________________________

To run ringOS within Qemu on Linux or Windows:

**Windows** double-click the  `run2.bat` file to initialize a Qemu VM and run ringOS.

**Linux** `make run`

## Compile and run the latest stable release

[Shell scipt](https://github.com/ringwormGO-organization/ringOS/blob/main-and-beta-things/ringOS-stable-Builder.sh)

[Manually download binary](https://github.com/ringwormGO-organization/ringOS/releases/tag/ringOSv2.0.0)

______

## Install Qemu

**Windows** Download executable file, run it (https://www.qemu.org/download/#windows) and add Qemu to PATH

**Linux** `sudo apt install qemu-system-x86`
___
## Running in Virtual Box or VMWare

**Recommended RAM: ~4096MB**

You need install two more packages:

`sudo apt-get install xorriso`

`sudo apt-get install mkisofs`

For Red Hat(-based) distros:

`sudo yum install xorriso`

`sudo yum install mkisofs`

From now you can simply enter bin directory and run [shell script](https://github.com/ringwormGO-organization/ringOS/blob/main/ringOS-Beta17/ISO.sh)

Enter kernel/bin directory.

Type these commands in order:

`mkdir -p iso`

`rm -rf iso/*.iso`

`rm -rf iso/*.img`

`cp ringOS.img iso`

`xorriso -as mkisofs -R -f -e ringOS.img -no-emul-boot -o ./iso/ringOS.iso iso`

Open VirtualBox, create new virtual machine and put ISO as CD-ROM device and enable ICH9 CPU chipset.

Open VMWare Workstation, create new virtual machine, put ISO, enter Boot Manager by pressing **ESC** during boot and select **EFI Internal Shell**.

![image](https://user-images.githubusercontent.com/83548580/143719557-aee05602-e163-4693-a124-2307aa09eac0.png)

![image](https://user-images.githubusercontent.com/83548580/143719800-0600b9fe-8ca7-48bd-bd24-edc6c3048d56.png)

- - - - - - 

![image](https://user-images.githubusercontent.com/83548580/149768519-9a16bc9d-dd7e-4e29-8941-86f9733e19f0.png)

![image](https://user-images.githubusercontent.com/83548580/143719473-982e21ff-def5-4383-aa4f-3b249eab4e90.png)

(You can execute this commands in WSL and run VirtualBox on Windows)

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
## Settings
Check [settings.h](https://github.com/ringwormGO-organization/ringOS/blob/main/kernel/src/settings.h) for more info.

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
