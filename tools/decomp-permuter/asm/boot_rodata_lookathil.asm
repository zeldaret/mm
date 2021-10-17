.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_800992F0
/* 025764 0x800992F0 */ .word	0x3FB99999
/* 025765 0x800992F4 */ .word	0x9999999A
glabel D_800992F8
/* 025766 0x800992F8 */ .word	0x3FB99999
/* 025767 0x800992FC */ .word	0x9999999A
