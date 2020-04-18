#!/bin/bash

if [ "$#" -ne "2" ];
then
    echo "usage: $0 file_name src_path"
    echo "e.g. $0 z_actor code"
    exit 1
fi

# Split asm file, create base c file, and add it to the list of non-matchings
tools/split_asm.py -c "src/$2/$1.c" "asm/$1.asm" "asm/non_matchings/$1"
echo "$1" >> tables/files_with_nonmatching.txt

# Edit linker script to use new .c file
sed -i "s/asm\/$1.o/src\/${2//\//\\\/}\/$1.o/g" linker_scripts/code_script.txt

# Build with new file
make build/code.elf

# Copy newly-built .o file to expected/ for use by the diff script
mkdir -p "expected/build/src/$2/"
cp "build/src/$2/$1.o" "expected/build/src/$2/$1.o"