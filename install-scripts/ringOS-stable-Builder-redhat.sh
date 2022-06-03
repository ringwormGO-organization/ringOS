#!/bin/bash

echo "ringOS stable builder for Fedora(-based) Linux"
echo "This script will ask you for password using ."
echo "Note: On Red Hat Enterprise Linux & CentOS, you might need to install the EPEL repository. "
echo "THIS SCRIPT HAS NOT BEEN TESTED AND IT IS EXTREMELY UNSTABLE! USE WITH CAUTION!!!!!!! IF YOU WANT TO IMPROVE, CONSIDER A PULL REQUEST."
echo "Note: To install NASM on CentOS & RHEL, please enable the CodeReady Linux Builder (PowerTools) repository. "

yum check-update && echo Check for update successful || echo FAILED to check for update
yum group install "Development tools" && echo Development tools installed successfully || echo FAILED to install Development tools
yum install nasm && echo NASM installed successfully || echo FAILED to install nasm
yum install qemu-kvm && echo Qemu-kvm installed successfully || echo FAILED to install Qemu-kvm
yum install git && echo git installed successfully || echo FAILED to install git
yum install lld && echo lld installed successfully || echo FAILED to install lld
yum install xorriso && echo xorriso installed successfully || echo FAILED to install xorriso
yum install mkisofs && echo mkisofs installed successfully || echo FAILED to install mkisofs

mkdir "ringOS-stable" && echo ringOS-stable directory successfully created || echo FAILED to create ringOS directory

cd ringOS-stable && echo Successfully enter ringOS-stable directory || echo FAILED to enter ringOS-stable directory

git clone -b ringOS-stable2 https://github.com/ringwormGO-organization/ringOS && echo Cloning successful || echo FAILED to clone

cd ringOS && echo In ringOS directory || echo FAILED to enter ringOS directory

cd ringOS && echo In ringOS directory || echo FAILED to enter ringOS directory
cd gnu-efi && echo In gnu-efi directory || echo FAILED to enter gnu-efi directory
make bootloader && echo Bootloader successfully created || echo FAILED to create bootloader
cd ../kernel && echo In kernel directory || echo FAILED to enter kernel directory
sed -i 's/qemu-system-x86_64/\/usr\/libexec\/qemu-kvm/g' Makefile
make kernel && echo Kernel successfully created || echo FAILED to create kernel
make buildimg && echo Buildimg successfully created || echo FAILED to create buildimg
chmod +x ./ISO.sh
./ISO.sh
make run && echo Successfully run ringOS stable release || echo FAILED run ringOS stable release

