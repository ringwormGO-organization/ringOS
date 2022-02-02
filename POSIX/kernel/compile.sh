# Compile POSIX

# Type this in terminal: chmod +x ./compile.sh
# And then: ./compile.sh

cd ../
git clone https://gitlab.com/bztsrc/posix-uefi.git
cd POSIX
ln -s ../posix-uefi/uefi

clear && make