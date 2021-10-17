.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel gFramerateDivisor
/* 306832 0x801D1500 */ .word	0x00000001
glabel gFramerateDivisorF
/* 306833 0x801D1504 */ .word	0x3F800000
glabel gFramerateDivisorHalf
/* 306834 0x801D1508 */ .word	0x3F000000
glabel gFramerateDivisorThird
/* 306835 0x801D150C */ .word	0x3EAAAAAB
glabel D_801D1510
/* 306836 0x801D1510 */ .word	0x0000000A
glabel D_801D1514
/* 306837 0x801D1514 */ .word	0x00000000
/* 306838 0x801D1518 */ .word	0x00000000
/* 306839 0x801D151C */ .word	0x00000000
