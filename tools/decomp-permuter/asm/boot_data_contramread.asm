.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80097FB0
/* 024532 0x80097FB0 */ .word	0xFFFFFFFF
/* 024533 0x80097FB4 */ .word	0x00000000
/* 024534 0x80097FB8 */ .word	0x00000000
/* 024535 0x80097FBC */ .word	0x00000000
