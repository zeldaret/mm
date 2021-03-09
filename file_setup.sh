#!/bin/bash

if [ "$#" -lt "2" ];
then
    echo "usage: $0 file_name src_path [non_matching_path]"
    echo "e.g. $0 z_actor code"
    exit 1
fi

# If there are only two arguments, then we will use the non_matchings path to be the same as src_path
if [ "$#" -eq "2" ];
then
	3=$2
fi

# Split asm file, create base c file, and add it to the list of non-matchings
tools/split_asm.py -c "src/$2/$1.c" "asm/$1.asm" "asm/non_matchings/$3/$1"
echo "$1" >> tables/files_with_nonmatching.txt

# Edit linker script to use new .c file
sed -i "s/asm\/$1.o/src\/${2//\//\\\/}\/$1.o/g" linker_scripts/code_script.txt

# Build with new file
make diff-init
