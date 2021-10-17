.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_800992C0
/* 025752 0x800992C0 */ .word	0x3F91DF46
/* 025753 0x800992C4 */ .word	0x9D353918
/* 025754 0x800992C8 */ .word	0x00000000
/* 025755 0x800992CC */ .word	0x00000000
