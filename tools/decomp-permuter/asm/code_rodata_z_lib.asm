.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DDA80
/* 319472 0x801DDA80 */ .word	0x38000100
glabel D_801DDA84
/* 319473 0x801DDA84 */ .word	0x38000100
/* 319474 0x801DDA88 */ .word	0x00000000
/* 319475 0x801DDA8C */ .word	0x00000000
