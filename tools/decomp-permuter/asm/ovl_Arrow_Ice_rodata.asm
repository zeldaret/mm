.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

/* 001908 0x80924200 */ .word	0xBEC3CCC7
/* 001909 0x80924204 */ .word	0x00000000
glabel D_80924208
/* 001910 0x80924208 */ .word	0x446D8000
glabel D_8092420C
/* 001911 0x8092420C */ .word	0x3EAAAAAB
