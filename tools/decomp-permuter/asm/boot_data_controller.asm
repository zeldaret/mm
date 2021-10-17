.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80097E40
/* 024440 0x80097E40 */ .word	0x00000000
/* 024441 0x80097E44 */ .word	0x00000000
/* 024442 0x80097E48 */ .word	0x00000000
/* 024443 0x80097E4C */ .word	0x00000000
