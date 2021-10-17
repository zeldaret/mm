.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DD7B0
/* 319292 0x801DD7B0 */ .word	0x3D088889
/* 319293 0x801DD7B4 */ .word	0x00000000
/* 319294 0x801DD7B8 */ .word	0x00000000
/* 319295 0x801DD7BC */ .word	0x00000000
