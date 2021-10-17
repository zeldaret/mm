.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DE5D0
/* 320196 0x801DE5D0 */ .word	0x3A03126F
/* 320197 0x801DE5D4 */ .word	0x00000000
/* 320198 0x801DE5D8 */ .word	0x00000000
/* 320199 0x801DE5DC */ .word	0x00000000
