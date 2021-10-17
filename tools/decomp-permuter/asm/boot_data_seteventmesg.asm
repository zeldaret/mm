.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80097F10
/* 024492 0x80097F10 */ .word	0x00000000
/* 024493 0x80097F14 */ .word	0x00000000
/* 024494 0x80097F18 */ .word	0x00000000
/* 024495 0x80097F1C */ .word	0x00000000
