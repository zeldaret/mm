#!/bin/bash

if [ "$#" -ne "1" ];
then
    echo "usage: $0 func_name"
    exit 1
fi

tools/asm-differ/diff.py -mwo $1
