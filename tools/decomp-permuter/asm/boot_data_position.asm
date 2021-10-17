.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80097F80
/* 024520 0x80097F80 */ .word	0x3C8EFA35
/* 024521 0x80097F84 */ .word	0x00000000
/* 024522 0x80097F88 */ .word	0x00000000
/* 024523 0x80097F8C */ .word	0x00000000
