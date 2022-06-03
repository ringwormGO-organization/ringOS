#!/bin/bash

echo "ringOS beta builder for Arch(-based) Linux"
echo "Please run this script as root."

pacman -Sy base-devel mtools && echo base-devel and mtools installed successfully || echo FAILED to install base-devel and/or mtools
pacman -S mtools && echo build-essential mtools installed successfully || echo FAILED to install build-essential tools
pacman -S nasm && echo NASM installed successfully || echo FAILED to install nasm
pacman -S qemu-x86_64 && echo Qemu installed successfully || echo FAILED to install Qemu
pacman -S git && echo git installed successfully || echo FAILED to install git
pacman -S lld && echo lld installed successfully || echo FAILED to install lld
pacman -S xorriso && echo xorriso installed successfully || echo FAILED to install xorriso
pacman -Ss mkisofs && echo mkisofs installed successfully || echo FAILED to install mkisofs

git clone https://github.com/ringwormGO-organization/ringOS

cd ringOS

chmod +x ./compile.sh
./compile.sh

