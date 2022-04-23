#!/bin/bash

clear

sudo pacman -Sy base-devel mtools && echo base-devel installed successfully || echo FAILED to install base-devel
sudo pacman -S mtools && echo build-essential mtools installed successfully || echo FAILED to install build-essential tools
sudo pacman -S nasm && echo NASM installed successfully || echo FAILED to install nasm
sudo pacman -S qemu-x86_64 && echo Qemu installed successfully || echo FAILED to install Qemu
sudo pacman -S git && echo git installed successfully || echo FAILED to install git
sudo pacman -S lld && echo lld installed successfully || echo FAILED to install lld
sudo pacman -S xorriso && echo xorriso installed successfully || echo FAILED to install xorriso
sudo pacman -Ss mkisofs && echo mkisofs installed successfully || echo FAILED to install mkisofs

git clone https://github.com/VanGutan/gnu-efi
mv bootloader gnu-efi/bootloader

cd gnu-efi && echo In gnu-efi directory || echo FAILED to enter gnu-efi directory
make bootloader && echo Bootloader successfully created || echo FAILED to create bootloader
cd ../kernel && echo In kernel directory || echo FAILED to enter kernel directory
make kernel && echo Kernel successfully created || echo FAILED to create kernel
make buildimg && echo Buildimg successfully created || echo FAILED to create buildimg
chmod +x ./ISO.sh
./ISO.sh
make run
cd ../
chmod +x ./clean.sh
./clean.sh
