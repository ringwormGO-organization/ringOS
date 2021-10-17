# DOCUMENTATION
Documentation is for ringOS.

# Compile
### Software you need
1. [Qemu](#install-qemu)
2. WSL or Linux

### Type of release
Download zip file in Qemu release (https://github.com/Andrej123456789/ringOS/releases/tag/Beta11_Qemu).

### Compiling
Unzip zip file and navigate folder to your Terminal (Linux) or WSL on Windows (`cd`).

This commands is for Linux based distros and WSL.

If you first time running WSL or Linux installation, follow these steps:

`sudo apt update`

`sudo apt-get install build-essential mtools`

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

**Linux** `sudo apt install qemu-system-x86_64`

# Other

If you have probelm or idea create issue.

This documentation will continue improving based on new features in ringOS.

For ringOSY documentation visit: https://github.com/Andrej123456789/ringOS/blob/Beta11_Qemu/ringOSY/README.md

___

Thanks for choosing ringOS

©ringwormGO 2021
