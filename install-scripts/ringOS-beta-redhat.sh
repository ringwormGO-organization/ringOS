#!/bin/bash

echo "ringOS beta builder for Fedora(-based) Linux"
echo "Please run this script as root."
echo "Note: On Red Hat Enterprise Linux & CentOS, you might need to install the EPEL repository. "
echo "THIS SCRIPT HAS NOT BEEN TESTED AND IT IS EXTREMELY UNSTABLE! USE WITH CAUTION!!!!!!! IF YOU WANT TO IMPROVE, CONSIDER A PULL REQUEST."
echo "Note: To install NASM on CentOS or RHEL, you will need to enable the CodeReady Linux Builder (PowerTools) repository. "

yum check-update && echo Check for update successful || echo FAILED to check for update
yum group install "Development tools" && echo Development tools installed successfully || echo FAILED to install Development tools
yum install nasm && echo NASM installed successfully || echo FAILED to install nasm
yum install qemu-kvm && echo Qemu-kvm installed successfully || echo FAILED to install Qemu-kvm
yum install git && echo git installed successfully || echo FAILED to install git
yum install lld && echo lld installed successfully || echo FAILED to install lld
yum install xorriso && echo xorriso installed successfully || echo FAILED to install xorriso
yum install mkisofs && echo mkisofs installed successfully || echo FAILED to install mkisofs

git clone https://github.com/ringwormGO-organization/ringOS

cd ringOS

sed -i 's/qemu-system-x86_64/"\/usr\/libexec\/qemu-kvm"/g' GNUmakefile

chmod +x ./compile.sh
./compile.sh
