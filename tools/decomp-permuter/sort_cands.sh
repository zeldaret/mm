#!/bin/bash

if [[ $1 < 2 ]]; then
    echo "Usage: $0 output_dir"
    echo "Ex: $0 nonmatchings/func_80000000"
    exit 1
fi
if [[ ! -d $1 ]]; then
    echo "Argument must be a directory"
    exit 1
fi

find $1 -name score.txt -exec echo -n {}\  \; -exec cat {} \; | sort -rnk2
