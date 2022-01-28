#!/bin/bash

shopt -s globstar

if [ "$#" -ne "2" ];
then
    echo "usage: $0 old_name new_name"
    exit 1
fi

#echo "Replace $1 with $2?"
#read
grep -rl "$1" asm/**/*.s src/**/*.{c,h} include/**/*.h tools/disasm/functions.txt tools/disasm/variables.txt tools/sizes/*.csv | xargs sed -i "s/\b$1\b/$2/g"
