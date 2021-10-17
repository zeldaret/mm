.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80097500
/* 023848 0x80097500 */ .word	0x00000000
/* 023849 0x80097504 */ .word	0x00000000
/* 023850 0x80097508 */ .word	0x00000000
/* 023851 0x8009750C */ .word	0x00000000
/* 023852 0x80097510 */ .word	0x7F800000
/* 023853 0x80097514 */ .word	0xFF800000
/* 023854 0x80097518 */ .word	0x00000000
/* 023855 0x8009751C */ .word	0x80000000
/* 023856 0x80097520 */ .word	0x7FBFFFFF
glabel D_80097524
/* 023857 0x80097524 */ .word	0x7F810000
/* 023858 0x80097528 */ .word	0x7FFFFFFF
/* 023859 0x8009752C */ .word	0x00000000
