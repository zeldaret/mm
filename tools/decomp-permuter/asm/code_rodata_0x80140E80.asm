.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DF120
/* 320920 0x801DF120 */ .word	0x3D03126F
glabel D_801DF124
/* 320921 0x801DF124 */ .word	0x3D03126F
/* 320922 0x801DF128 */ .word	0x00000000
/* 320923 0x801DF12C */ .word	0x00000000
