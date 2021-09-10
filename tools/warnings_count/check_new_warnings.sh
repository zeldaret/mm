#!/bin/bash
set -e

# This script can be used when you want to test locally the amount of warnings produced by your changes before doing a PR.

DIR="$(dirname "$(readlink -f "$0")")"
cd "$DIR/../.."

remove_ansi_codes () {
    perl -pe '
    s/\e\[[\x30-\x3f]*[\x20-\x2f]*[\x40-\x7e]//g;
    s/\e[PX^_].*?\e\\//g;
    s/\e\][^\a]*(?:\a|\e\\)//g;
    s/\e[\[\]A-Z\\^_@]//g;' $1
}

make_warnings () {
    make $1 2> >(tee tools/warnings_count/warnings_temp.txt) \
    && remove_ansi_codes tools/warnings_count/warnings_temp.txt > tools/warnings_count/warnings_$2_new.txt \
    && rm tools/warnings_count/warnings_temp.txt
}

compare_warnings () {
    python3 tools/warnings_count/compare_warnings.py tools/warnings_count/warnings_$1_current.txt tools/warnings_count/warnings_$1_new.txt    
}

make distclean
make_warnings setup setup
make_warnings disasm disasm
make_warnings all build

compare_warnings setup
compare_warnings disasm
compare_warnings build
