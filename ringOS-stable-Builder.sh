clear

sudo apt upgrade && echo Upgrade successful || echo FAILED to upgrade
sudo apt-get install build-essential mtools && echo build-essential mtools insatlled successfully || echo FAILED to install build-essential tools
sudo apt-get install nasm && echo NASM insatlled successfully || echo FAILED to install nasm
sudo apt-get install qemu-system-x86 && echo Qemu insatlled successfully || echo FAILED to install Qemu
sudo apt-get install git && echo git insatlled successfully || echo FAILED to install git
sudo apt-get install lld && echo lld installed successfully || echo FAILED to install lld
sudo apt-get install xorriso && echo xorriso installed successfully || echo FAILED to install xorriso
sudo apt-get install mkisofs && echo mkisofs installed successfully || echo FAILED to install mkisofs

mkdir "ringOS-stable" && echo ringOS-stable directory successfully created || echo FAILED to create ringOS directory

cd ringOS-stable && Successfully enter ringOS-stable directory || echo FAILED to enter ringOS-stable directory

git clone -b ringOS-stable2 https://github.com/ringwormGO-organization/ringOS && echo Cloning successful || echo FAILED to clone

cd ringOS && echo In ringOS directory || echo FAILED to enter ringOS directory

cd ringOS && echo In ringOS directory || echo FAILED to enter ringOS directory
cd gnu-efi && echo In gnu-efi directory || echo FAILED to enter gnu-efi directory
make bootloader && echo Bootloader successfully created || echo FAILED to create bootloader
cd ../kernel && echo In kernel directory || echo FAILED to enter kernel directory
make kernel && echo Kernel successfully created || echo FAILED to create kernel
make buildimg && echo Buildimg successfully created || echo FAILED to create buildimg
./ISO.sh
make run && echo Successfully run ringOS stable release || echo FAILED run ringOS stable release
