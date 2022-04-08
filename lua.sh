clear

wget https://www.lua.org/ftp/lua-5.4.4.tar.gz
tar -xvf lua-5.4.4.tar.gz
mv lua-5.4.4 kernel/src/port
rm *.tar.gz

cd kernel/src/port/lua-5.4.4
    echo 'gcc = x86_64-elf-gcc -std=gnu99' >> Makefile
    make generic
cd ..
