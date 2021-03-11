#!/bin/bash

if [ "$#" -lt "2" ];
then
    echo "usage: $0 file_name src_path [non_matching_path]"
    echo "e.g. $0 z_actor code"
    exit 1
fi

code_file=$1
code_path=$2

# If there are only two arguments, then we will use the non_matchings path to be the same as src_path
if [ "$#" -eq "2" ];
then
	code_bucket=$code_path
else
	code_bucket=$3
fi

# Split asm file, create base c file, and add it to the list of non-matchings
tools/split_asm.py -c "./src/$code_path/$code_file.c" "./asm/$code_bucket/$code_file.asm" "./asm/non_matchings/$code_bucket/$code_file"
echo "$code_bucket/$code_file" >> tables/files_with_nonmatching.txt

# Edit linker script to use new .c file
sed -i "s/asm\/$code_file.o/src\/${2//\//\\\/}\/$code_file.o/g" linker_scripts/code_script.txt

# Build with new file
make -j diff-init
