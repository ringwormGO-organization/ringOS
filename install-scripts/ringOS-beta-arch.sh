#!/bin/bash

echo "ringOS beta builder for Arch(-based) Linux"
echo "This script will ask you for password using sudo."

sudo pacman -Sy base-devel mtools && echo base-devel and mtools installed successfully || echo FAILED to install base-devel and/or mtools
sudo pacman -S mtools && echo build-essential mtools installed successfully || echo FAILED to install build-essential tools
sudo pacman -S nasm && echo NASM installed successfully || echo FAILED to install nasm
sudo pacman -S qemu-x86_64 && echo Qemu installed successfully || echo FAILED to install Qemu
sudo pacman -S git && echo git installed successfully || echo FAILED to install git
sudo pacman -S lld && echo lld installed successfully || echo FAILED to install lld
sudo pacman -S xorriso && echo xorriso installed successfully || echo FAILED to install xorriso
sudo pacman -Ss mkisofs && echo mkisofs installed successfully || echo FAILED to install mkisofs

git clone https://github.com/ringwormGO-organization/ringOS

cd ringOS

chmod +x ./compile.sh
./compile.sh