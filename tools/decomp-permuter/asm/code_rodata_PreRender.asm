.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DFC60
/* 321640 0x801DFC60 */ .word	0x736C6F77
/* 321641 0x801DFC64 */ .word	0x6C790000
/* 321642 0x801DFC68 */ .word	0x00000000
/* 321643 0x801DFC6C */ .word	0x00000000
