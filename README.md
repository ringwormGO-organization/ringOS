# LockOS
LockOS source code

# About LockOS
LockOS is beta version of ringOS. ringOS is ringwormGO operating system
ringOS is keyboard oriented OS with GUI elements

This repo is for developing and invitation new contributors for this project.

![image](https://user-images.githubusercontent.com/83548580/133824416-455bc2d8-3364-4ffd-abd6-24bff779af32.png)
Beta 4

# System requiratmens
**UEFI VERSION** | UEFI 64 bit PC

**BIOS VERSION** | BIOS 32/64 bit PC

# BIOS version
In src folder
Run build.bat to run BIOS supprot

BIOS version is not officialy supproted by ringwormGO. Check out https://github.com/lightning-speed/Radical for genuine supprot

# Run LockOS BIOS
**Windows**
"qemu-system-x86_64.exe -M q35 -cpu max -smp 2 -m 512M -boot d -rtc base=localtime -serial stdio -cdrom C:\Users\vangu\Downloads\LockOS.iso"

**Linux**
"qemu-system-x86_64 -accel kvm -M q35 -cpu max -smp 12 -m 512M -boot d -rtc base=localtime -serial stdio -cdrom (Path here)

C:\Users\vangu\Downloads\LockOS.iso = ISO path on Windows

# ringwormGO GitHub repo link
https://github.com/ringwormGO/ringwormGO
Also, here is final version (when come)

# Discord Server
https://discord.gg/G9ScDxz8

# Resources used:
https://www.youtube.com/playlist?list=PLxN4E629pPnJxCQCLy7E0SQY_zuumOVyZ | 
https://discord.gg/KFjvywqr
