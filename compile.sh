#!/bin/bash

clear
make

if [ "$1" == "uefi" ]; then
    echo "Booting in UEFI mode..."
    make run-uefi

else
    echo "Booting in BIOS mode..."
    make run

fi

make clean