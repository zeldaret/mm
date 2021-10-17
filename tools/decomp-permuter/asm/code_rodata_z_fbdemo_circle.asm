.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DF9E0
/* 321480 0x801DF9E0 */ .word	0x3DCCCCCD
glabel D_801DF9E4
/* 321481 0x801DF9E4 */ .word	0xC47FC000
glabel D_801DF9E8
/* 321482 0x801DF9E8 */ .word	0xC47FC000
glabel D_801DF9EC
/* 321483 0x801DF9EC */ .word	0xC47FC000
glabel D_801DF9F0
/* 321484 0x801DF9F0 */ .word	0xC47FC000
glabel D_801DF9F4
/* 321485 0x801DF9F4 */ .word	0xC47FC000
glabel D_801DF9F8
/* 321486 0x801DF9F8 */ .word	0xC47FC000
/* 321487 0x801DF9FC */ .word	0x00000000
