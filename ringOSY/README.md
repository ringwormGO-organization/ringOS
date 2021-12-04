
# How to develop for ringOSY
https://www.youtube.com/playlist?list=PLZQftyCk7_SeZRitx5MjBKzTtvk0pHMtp

https://github.com/ringwormGO-organization/ringOS/blob/ringOSY/README.md#non-docker-build-enviroment

# System requiretmens for developing:
  1. Qemu (for virtual machine)
  2. WSL 2
  3. Docker Desktop
  4. Visual Studio Code
  5. Rufus (for real hardware)
  6. Powershell (if you use Windows)
  
If you have problem with running ringOSY, create new issue or check out https://github.com/davidcallanan/os-series


## Setup

Build an image for our build-environment:
 - `docker build buildenv -t myos-buildenv`

## Build

Enter build environment:
 - Linux or MacOS: `docker run --rm -it -v "$(pwd)":/root/env myos-buildenv`
 - Windows (CMD): `docker run --rm -it -v "%cd%":/root/env myos-buildenv`
 - Windows (PowerShell): `docker run --rm -it -v "${pwd}:/root/env" myos-buildenv`
 - Please use the linux command if you are using `WSL`, `msys2` or `git bash`
 - NOTE: If you are having trouble with an unshared drive, ensure your docker daemon has access to the drive you're development environment is in. For Docker Desktop, this is in "Settings > Shared Drives" or "Settings > Resources > File Sharing".

Build for x86 (other architectures may come in the future):
 - `make build-x86_64`
 - If you are using Qemu, please close it before running this command to prevent errors.

To leave the build environment, enter `exit`.

## Emulate

You can emulate your operating system using [Qemu](https://www.qemu.org/): (Don't forget to [add qemu to your path](https://dev.to/whaleshark271/using-qemu-on-windows-10-home-edition-4062#:~:text=2.-,Add%20Qemu%20path%20to%20environment%20variables%20settings,-Copy%20the%20Qemu)!)

 - `qemu-system-x86_64 -cdrom dist/x86_64/kernel.iso`
 - Note: Close the emulator when finished, so as to not block writing to `kernel.iso` for future builds.

If the above command fails, try one of the following:
 - Windows: [`qemu-system-x86_64 -cdrom dist/x86_64/kernel.iso -L "C:\Program Files\qemu"`](https://stackoverflow.com/questions/66266448/qemu-could-not-load-pc-bios-bios-256k-bin)
 - Linux: [`qemu-system-x86_64 -cdrom dist/x86_64/kernel.iso -L /usr/share/qemu/`](https://unix.stackexchange.com/questions/134893/cannot-start-kvm-vm-because-missing-bios)
 - Alternatively, install a custom BIOS binary file and link it to Qemu using the `-L` option.

Alternatively, you should be able to load the operating system on a USB drive (MBR partition style) and boot into it when you turn on your computer.


# NON-DOCKER BUILD ENVIROMENT
This work on native Linux and WSL

Type all commands in terminal:

sudo apt update

sudo apt install build-essential

sudo apt install bison

sudo apt install flex

sudo apt install libgmp3-dev

sudo apt install libmpc-dev

sudo apt install libmpfr-dev

sudo apt install texinfo

export PREFIX="/usr/local/x86_64elfgcc"

export TARGET=x86_64-elf

export PATH="$PREFIX/bin:$PATH"

mkdir /tmp/src

cd /tmp/src

curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.35.1.tar.gz

tar xf binutils-2.35.1.tar.gz

mkdir binutils-build

cd binutils-build

../binutils-2.35.1/configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$PREFIX 2>&1 | tee configure.log

sudo make all install 2>&1 | tee make.log

cd /tmp/src

curl -O https://ftp.gnu.org/gnu/gcc/gcc-10.2.0/gcc-10.2.0.tar.gz

tar xf gcc-10.2.0.tar.gz

mkdir gcc-build

cd gcc-build

../gcc-10.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-libssp --enable-languages=c++ --without-headers

sudo make all-gcc

sudo make all-target-libgcc

sudo make install-gcc

sudo make install-target-libgcc

-----------

Now you need add folder to variable.

Type ```sudo nano ~/.bashrc```

Scroll to end of file and type: ```export PATH="$PATH:/usr/local/x86_64/elfgcc/bin"``` save it and restart system (if you are using native Linux) or WSL.

Check if it was successful with: ```x86_64-elf-gcc```.

ringOSY compile with: ```make build-x86_64```.

_________

Thanks for choosing ringOSY

©2021 ringwormGO
