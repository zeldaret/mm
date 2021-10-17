.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

/* 001900 0x809260B0 */ .word	0xBEC3CCC7
/* 001901 0x809260B4 */ .word	0x00000000
glabel D_809260B8
/* 001902 0x809260B8 */ .word	0x446D8000
glabel D_809260BC
/* 001903 0x809260BC */ .word	0x3EAAAAAB
