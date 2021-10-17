.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80097FA0
/* 024528 0x80097FA0 */ .word	0x1E6E0856
glabel D_80097FA4
/* 024529 0x80097FA4 */ .byte	0x03
glabel D_80097FA5
/* 024529 0x80097FA4 */ .byte	0x00
/* 024529 0x80097FA4 */ .short	0x0000
/* 024530 0x80097FA8 */ .word	0x00000000
/* 024531 0x80097FAC */ .word	0x00000000
