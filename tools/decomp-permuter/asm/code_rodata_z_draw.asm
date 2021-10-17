.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DD770
/* 319276 0x801DD770 */ .word	0x3F333333
glabel D_801DD774
/* 319277 0x801DD774 */ .word	0x3CA3D70A
/* 319278 0x801DD778 */ .word	0x00000000
/* 319279 0x801DD77C */ .word	0x00000000
