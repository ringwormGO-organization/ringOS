clear

sudo apt upgrade && echo Upgrade successful || echo FAILED to upgrade
sudo apt-get install build-essential mtools && echo build-essential mtools insatlled successfully || echo FAILED to install build-essential tools
sudo apt-get install nasm && echo NASM insatlled successfully || echo FAILED to install nasm
sudo apt-get install qemu-system-x86 && echo Qemu insatlled successfully || echo FAILED to install Qemu
sudo apt-get install git && echo git insatlled successfully || echo FAILED to install git
sudo apt-get install lld && echo lld installed successfully || echo FAILED to install lld
sudo apt-get install xorriso && echo xorriso installed successfully || echo FAILED to install xorriso
sudo apt-get install mkisofs && echo mkisofs installed successfully || echo FAILED to install mkisofs

git clone -b main https://github.com/ringwormGO-organization/ringOS
cd ringOS

git clone https://github.com/VanGutan/gnu-efi
mv bootloader gnu-efi/bootloader

git clone https://github.com/VanGutan/ringOS-Beta14-OVMFTemplate
mv ringOS-Beta14-OVMFTemplate OVMFbin

cd gnu-efi && echo In gnu-efi directory || echo FAILED to enter gnu-efi directory
make bootloader && echo Bootloader successfully created || echo FAILED to create bootloader
cd ../kernel && echo In kernel directory || echo FAILED to enter kernel directory
make kernel && echo Kernel successfully created || echo FAILED to create kernel
make buildimg && echo Buildimg successfully created || echo FAILED to create buildimg
./ISO.sh
make run
