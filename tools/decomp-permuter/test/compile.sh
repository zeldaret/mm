#!/bin/bash
mips-linux-gnu-gcc -O2 -fno-PIC -fno-common -ffreestanding -mno-shared -mno-abicalls -G 0 -c "$@"
