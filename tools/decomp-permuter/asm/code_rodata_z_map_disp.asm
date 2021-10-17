.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DDAC0
/* 319488 0x801DDAC0 */ .word	0xBFCCCCCD
glabel D_801DDAC4
/* 319489 0x801DDAC4 */ .word	0x3ECCCCCD
glabel D_801DDAC8
/* 319490 0x801DDAC8 */ .word	0x3B3B3EE7
glabel D_801DDACC
/* 319491 0x801DDACC */ .word	0x3D4CCCCD
glabel D_801DDAD0
/* 319492 0x801DDAD0 */ .word	0xBFCCCCCD
glabel D_801DDAD4
/* 319493 0x801DDAD4 */ .word	0x3ECCCCCD
glabel D_801DDAD8
/* 319494 0x801DDAD8 */ .word	0x3D4CCCCD
glabel D_801DDADC
/* 319495 0x801DDADC */ .word	0x3D4CCCCD
