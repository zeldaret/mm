.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DD600
/* 319184 0x801DD600 */ .word	0x25730000
glabel D_801DD604
/* 319185 0x801DD604 */ .word	0x25730000
/* 319186 0x801DD608 */ .word	0x00000000
/* 319187 0x801DD60C */ .word	0x00000000
