#!/bin/bash

echo "ringOS stable builder for Debian(-based) Linux"
echo "This script will ask you for password using ."

apt-get update && echo Repository update successful || echo FAILED to update the repository
apt-get install build-essential mtools && echo build-essential mtools installed successfully || echo FAILED to install build-essential mtools
apt-get install nasm && echo NASM installed successfully || echo FAILED to install nasm
apt-get install qemu-system-x86 && echo Qemu installed successfully || echo FAILED to install Qemu
apt-get install git && echo git installed successfully || echo FAILED to install git
apt-get install lld && echo lld installed successfully || echo FAILED to install lld
apt-get install xorriso && echo xorriso installed successfully || echo FAILED to install xorriso
apt-get install mkisofs && echo mkisofs installed successfully || echo FAILED to install mkisofs

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

