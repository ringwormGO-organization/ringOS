#!/bin/bash

clear

pacman -Sy base-devel mtools && echo base-devel installed successfully || echo FAILED to install base-devel
pacman -S mtools && echo build-essential mtools installed successfully || echo FAILED to install build-essential tools
pacman -S nasm && echo NASM installed successfully || echo FAILED to install nasm
pacman -S qemu-x86_64 && echo Qemu installed successfully || echo FAILED to install Qemu
pacman -S git && echo git installed successfully || echo FAILED to install git
pacman -S lld && echo lld installed successfully || echo FAILED to install lld
pacman -S xorriso && echo xorriso installed successfully || echo FAILED to install xorriso
pacman -Ss mkisofs && echo mkisofs installed successfully || echo FAILED to install mkisofs

mkdir "ringOS-stable" && echo ringOS-stable directory successfully created || echo FAILED to create ringOS directory

cd ringOS-stable && echo Successfully enter ringOS-stable directory || echo FAILED to enter ringOS-stable directory

git clone -b ringOS-stable2 https://github.com/ringwormGO-organization/ringOS && echo Cloning successful || echo FAILED to clone

cd ringOS && echo In ringOS directory || echo FAILED to enter ringOS directory

cd ringOS && echo In ringOS directory || echo FAILED to enter ringOS directory
cd gnu-efi && echo In gnu-efi directory || echo FAILED to enter gnu-efi directory
make bootloader && echo Bootloader successfully created || echo FAILED to create bootloader
cd ../kernel && echo In kernel directory || echo FAILED to enter kernel directory
make kernel && echo Kernel successfully created || echo FAILED to create kernel
make buildimg && echo Buildimg successfully created || echo FAILED to create buildimg
chmod +x ./ISO.sh
./ISO.sh
make run && echo Successfully run ringOS stable release || echo FAILED run ringOS stable release

