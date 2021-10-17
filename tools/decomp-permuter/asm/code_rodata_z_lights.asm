.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DDAB0
/* 319484 0x801DDAB0 */ .word	0x4A895440
glabel D_801DDAB4
/* 319485 0x801DDAB4 */ .word	0x467F8000
glabel D_801DDAB8
/* 319486 0x801DDAB8 */ .word	0x360637BD
/* 319487 0x801DDABC */ .word	0x00000000
