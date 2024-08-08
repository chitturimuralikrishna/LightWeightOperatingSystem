#/bin/bash
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

cd build
mkdir -p idt
mkdir -p memory
cd ..

make all
