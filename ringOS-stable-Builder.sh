# © 2021 ringwormGO

#Type ./ringOS-stable-Builder-.sh to run script from terminal
#If don't work, chmod +x ringOS-stable-Builder-.sh and run script normally

#This script clonning ringOS stable release

clear

sudo apt upgrade && echo Upgrade successful || echo FAILED to upgrade
sudo apt-get install build-essential mtools && echo build-essential mtools insatlled successfully || echo FAILED to install build-essential tools
sudo apt install nasm && echo NASM insatlled successfully || echo FAILED to install nasm
sudo apt install qemu-system-x86 && echo Qemu insatlled successfully || echo FAILED to install Qemu

mkdir "ringOS-stable" && echo ringOS-stable directory successfully created || echo FAILED to create directory
gOS && echo In 
cd ringOS-stable && Successfully enter ringOS-stable directory || echo FAILED to enter ringOS-stable directory

git clone -b ringOS-stable1 https://github.com/ringwormGO-organization/ringOS && echo Cloning successful || echo FAILED to clone

cd ringOS && echo In ringOS directory || echo FAILED to enter ringOS directory

cd ringOS && echo In ringOS directory || echo FAILED to enter ringOS directory
cd gnu-efi && echo In gnu-efi directory || echo FAILED to enter gnu-efi directory
make bootloader && echo Bootloader successfully created || echo FAILED to create bootloader
cd ../kernel && echo In kernel directory || echo FAILED to enter kernel directory
make kernel && echo Kernel successfully created || echo FAILED to create kernel
make buildimg && echo Buildimg successfully created || echo FAILED to create buildimg
make run && echo Successfully run ringOS stable release || echo FAILED run ringOS stable release