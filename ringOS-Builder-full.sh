#Type ./ringOS-Builder-full.sh to run script from terminal
#If don't work, chmod +x ringOS-Builder-full.sh and run script normally

#This script clonning Beta14 template

# ©2021 ringwormGO

sudo apt upgrade && continue || echo FAILED to upgrade
sudo apt-get install build-essential mtools && continue || echo FAILED to install build-essential tools
sudo apt install nasm && continue || echo FAILED to install nasm
sudo apt install qemu-system-x86 && continue || echo FAILED to install Qemu
sudo apt install git && echo git insatlled successfully || echo FAILED to install git


[ -d "ringOS" ] && echo Directory exist || mkdir "ringOS"
[ -d "ringOS" ] && echo Directory created || echo FAILED to create/found directory ringOS


cd ringOS && echo In ringOS directory || echo FAILED to enter ringOS directory
git clone https://github.com/VanGutan/ringOS-Beta14-Template_gnu-efi && echo Cloning of gnu-efi successful || echo FAILED to clone gnu-efi
mv ringOS-Beta14-Template_gnu-efi gnu-efi && echo Renaming successful || echo FAILED to rename gnu-efi

cd gnu-efi && echo In gnu-efi directory || echo FAILED to enter gnu-efi directory
make bootloader && echo Bootloader successfully compiled || echo FAILED to compile bootloader

cd ../ && echo In ringOS directory || echo FAILED to enter ringOS directory

git clone https://github.com/VanGutan/ringOS-Beta14-KernelTemplate && echo Successfully cloned kernel || FAILED to clone kernel
mv ringOS-Beta14-KernelTemplate kernel && echo Renaming successful || echo FAILED to rename kernel

cd kernel && echo In kernel directory || echo FAILED to enter kernel directory
make kernel && echo Kernel compailed || echo FAILED to compile kernel

cd ../ && echo In ringOS directory || echo FAILED to enter ringOS directory

git clone https://github.com/VanGutan/ringOS-Beta14-OVMFTemplate && echo Successfully cloned OVMF || echo FAILED to clone OVMF
mv ringOS-Beta14-OVMFTemplate OVMFbin && echo Successfully renamed OVMF || FAILED to rename OVMF

cd kernel && echo In kernel directory || FAILED to enter kernel directory
make buildimg && echo Image created successfully || FAILED to create image
make run && echo Running ringOS || FAILED to run ringOS
