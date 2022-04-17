#!/bin/bash

cd bin
mkdir -p iso
rm -rf iso/*.iso
rm -rf iso/*.img
cp ringOS.img iso
xorriso -as mkisofs -R -f -e ringOS.img -no-emul-boot -o ./iso/ringOS.iso iso