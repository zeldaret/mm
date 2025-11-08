#!/usr/bin/env bash

shopt -s globstar

FUNCTIONS_FILES="tools/disasm/**/functions.txt"
VARIABLES_FILES="tools/disasm/**/variables.txt"
ASM_FILES="extracted/**/asm/**/*s"

if [ "$#" -ne "2" ];
then
    echo "usage: $0 old_name new_name"
    exit 1
fi

grep -rl "$1" src/**/*.{c,h} include/**/*.h assets/xml/* $FUNCTIONS_FILES $VARIABLES_FILES tools/sizes/*.csv | xargs sed -i "s/\b$1\b/$2/g"

# so many files it overloads xargs, and takes much longer
# grep -rl "$1" $ASM_FILES | xargs sed -i "s/\b$1\b/$2/g"
