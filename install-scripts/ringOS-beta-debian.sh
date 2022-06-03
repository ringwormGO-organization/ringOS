#!/bin/bash

echo "ringOS beta builder for Debian(-based) Linux"
echo "This script will ask you for password using sudo."

apt-get update && echo Repository update successful || echo FAILED to update the repository
apt-get install build-essential mtools && echo build-essential mtools installed successfully || echo FAILED to install build-essential and/or mtools
apt-get install nasm && echo NASM installed successfully || echo FAILED to install nasm
apt-get install qemu-system-x86 && echo Qemu installed successfully || echo FAILED to install Qemu
apt-get install git && echo git installed successfully || echo FAILED to install git
apt-get install lld && echo lld installed successfully || echo FAILED to install lld
apt-get install xorriso && echo xorriso installed successfully || echo FAILED to install xorriso
apt-get install mkisofs && echo mkisofs installed successfully || echo FAILED to install mkisofs

git clone https://github.com/ringwormGO-organization/ringOS

cd ringOS

chmod +x ./compile.sh
./compile.sh

