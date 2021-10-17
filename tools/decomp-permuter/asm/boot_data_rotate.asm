.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80097F90
/* 024524 0x80097F90 */ .word	0x3C8EFA35
/* 024525 0x80097F94 */ .word	0x00000000
/* 024526 0x80097F98 */ .word	0x00000000
/* 024527 0x80097F9C */ .word	0x00000000
