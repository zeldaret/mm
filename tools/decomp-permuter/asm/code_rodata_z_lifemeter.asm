.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DDA90
/* 319476 0x801DDA90 */ .word	0x3DCCCCCD
glabel D_801DDA94
/* 319477 0x801DDA94 */ .word	0x3DCCCCCD
glabel D_801DDA98
/* 319478 0x801DDA98 */ .word	0x3F2E147B
glabel D_801DDA9C
/* 319479 0x801DDA9C */ .word	0x3F2E147B
glabel D_801DDAA0
/* 319480 0x801DDAA0 */ .word	0x3EA3D70A
/* 319481 0x801DDAA4 */ .word	0x00000000
/* 319482 0x801DDAA8 */ .word	0x00000000
/* 319483 0x801DDAAC */ .word	0x00000000
