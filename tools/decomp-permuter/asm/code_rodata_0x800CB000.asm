.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DCDB0
/* 318652 0x801DCDB0 */ .word	0x3DCCCCCD
glabel D_801DCDB4
/* 318653 0x801DCDB4 */ .word	0x3DCCCCCD
/* 318654 0x801DCDB8 */ .word	0x00000000
/* 318655 0x801DCDBC */ .word	0x00000000
