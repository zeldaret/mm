.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel gScreenWidth
/* 306840 0x801D1520 */ .word	0x00000140
glabel gScreenHeight
/* 306841 0x801D1524 */ .word	0x000000F0
glabel startHeapSize
/* 306842 0x801D1528 */ .word	0x00000000
/* 306843 0x801D152C */ .word	0x00000000
