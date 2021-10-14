# DOCUMENTATION
Documentation is for ringOS.

# Compile
### Software you need
1. [Qemu](#install-qemu)
2. WSL or Linux

Download zip file in Qemu release (https://github.com/Andrej123456789/ringOS/releases/tag/Beta11_Qemu).

Unzip zip file and navigate folder to your Terminal (Linux) or WSL on Windows (`cd`).

If you first time running WSL or Linux installation, follow these steps:

`sudo apt update`

`sudo apt-get install build-essential mtools`

For compiling bootloader,
`cd gnu-efi`

`make bootloader`


For compiling kernel,

`cd kernel` or (if you are in gnu-efi folder) cd `../kernel`
`make kernel`

For running image,

**Windows** run `run2.bat` file

**Linux** `make run`



# Install Qemu

**Windows** Download executable file, run it (https://www.qemu.org/download/#windows) and add Qemu to PATH

**Linux** `sudo apt install qemu-system-x86` [Ubuntu based Linux distros]

# Other

If you have probelm or idea create issue.

This documentation will continue improving based on new features in ringOS.

For ringOSY documentation visit: https://github.com/Andrej123456789/ringOS/blob/Beta11_Qemu/ringOSY/README.md

Thanks for choosing ringOS
©ringwormGO 2021
