#!/usr/bin/env bash
for A in "$@"; do
    ./compile.sh "$A" && mips-linux-gnu-objdump -s "${A%.c}.o" > "${A%.c}.objdump"
done
