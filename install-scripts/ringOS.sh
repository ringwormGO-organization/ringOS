#!/bin/bash

clear

echo "Shell script designed for downloading and building ringOS"
echo "Root access is required for downloading packages"
echo " "

install()
{
    # Detect distro, credits to nanobyte for this part
    if [ -x "$(command -v apk)" ]; then
        echo "Alpine not yet supported."
        return
    elif [ -x "$(command -v apt-get)" ]; then
        apt-get update && echo Repository update successful || echo FAILED to update the repository
        apt-get install build-essential mtools && echo build-essential mtools installed successfully || echo FAILED to install build-essential and/or mtools
        apt-get install nasm && echo NASM installed successfully || echo FAILED to install nasm
        apt-get install qemu-system-x86 && echo Qemu installed successfully || echo FAILED to install Qemu
        apt-get install git && echo git installed successfully || echo FAILED to install git
        apt-get install lld && echo lld installed successfully || echo FAILED to install lld
        apt-get install xorriso && echo xorriso installed successfully || echo FAILED to install xorriso
        apt-get install mkisofs && echo mkisofs installed successfully || echo FAILED to install mkisofs
    elif [ -x "$(command -v dnf)" ]; then
        echo "Note: On Red Hat Enterprise Linux & CentOS, you might need to install the EPEL repository. "
        echo "THIS PART OF SCRIPT HAS NOT BEEN FULLY TESTED AND IT IS EXTREMELY UNSTABLE! USE WITH CAUTION!!!!!!! IF YOU WANT TO IMPROVE, CONSIDER A PULL REQUEST."
        echo "Note: To install NASM on CentOS & RHEL, please enable the CodeReady Linux Builder (PowerTools) repository. "
        echo " "

        dnf check-update && echo Check for update successful || echo FAILED to check for update
        dnf group install "Development tools" && echo Development tools installed successfully || echo FAILED to install Development tools
        dnf install nasm && echo NASM installed successfully || echo FAILED to install nasm
        dnf install qemu-kvm && echo Qemu-kvm installed successfully || echo FAILED to install Qemu-kvm
        dnf install git && echo git installed successfully || echo FAILED to install git
        dnf install lld && echo lld installed successfully || echo FAILED to install lld
        dnf install xorriso && echo xorriso installed successfully || echo FAILED to install xorriso
        dnf install genisoimage && echo genisoimage installed successfully || echo FAILED to install genisoimage
    elif [ -x "$(command -v yum)" ]; then
        echo "Note: On Red Hat Enterprise Linux & CentOS, you might need to install the EPEL repository. "
        echo "THIS PART OF SCRIPT HAS NOT BEEN FULLY TESTED AND IT IS EXTREMELY UNSTABLE! USE WITH CAUTION!!!!!!! IF YOU WANT TO IMPROVE, CONSIDER A PULL REQUEST."
        echo "Note: To install NASM on CentOS & RHEL, please enable the CodeReady Linux Builder (PowerTools) repository. "
        echo " "

        yum check-update && echo Check for update successful || echo FAILED to check for update
        yum group install "Development tools" && echo Development tools installed successfully || echo FAILED to install Development tools
        yum install nasm && echo NASM installed successfully || echo FAILED to install nasm
        yum install qemu-kvm && echo Qemu-kvm installed successfully || echo FAILED to install Qemu-kvm
        yum install git && echo git installed successfully || echo FAILED to install git
        yum install lld && echo lld installed successfully || echo FAILED to install lld
        yum install xorriso && echo xorriso installed successfully || echo FAILED to install xorriso
        yum install genisoimage && echo genisoimage installed successfully || echo FAILED to install genisoimage
    elif [ -x "$(command -v zypper)" ]; then
        echo "SUSE not yet supported."
        return
    elif [ -x "$(command -v pacman)" ]; then
        pacman -Sy base-devel mtools && echo base-devel and mtools installed successfully || echo FAILED to install base-devel and/or mtools
        pacman -S mtools && echo build-essential mtools installed successfully || echo FAILED to install build-essential tools
        pacman -S nasm && echo NASM installed successfully || echo FAILED to install nasm
        pacman -S qemu-system-x86 && echo Qemu installed successfully || echo FAILED to install Qemu
        pacman -S git && echo git installed successfully || echo FAILED to install git
        pacman -S lld && echo lld installed successfully || echo FAILED to install lld
        pacman -S xorriso && echo xorriso installed successfully || echo FAILED to install xorriso
        pacman -Ss mkisofs && echo mkisofs installed successfully || echo FAILED to install mkisofs
    else
        echo "Unknown and/or unsupported operating system!"; 
    fi
}

beta()
{
    git clone -b main https://github.com/ringwormGO-organization/ringOS
    cd ringOS
    chmod +x ./compile.sh
    ./compile.sh
}

stable()
{
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
}

read -p "Do you want to install packages? " yn
case $yn in
    [Yy]* ) install;;
    [Nn]* ) ;;
esac

read -p "Do you want to build beta version or stable version? [y - beta (latest version from latest commit from Github repo); n - stable (version 2)]? " yn
case $yn in
    [Yy]* ) beta;;
    [Nn]* ) stable;;
esac

echo "Done!"
