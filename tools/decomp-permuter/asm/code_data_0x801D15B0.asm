.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_801D15B0
/* 306876 0x801D15B0 */ .word	0x00000000
/* 306877 0x801D15B4 */ .word	0x00000000
/* 306878 0x801D15B8 */ .word	0x00000000
glabel D_801D15BC
/* 306879 0x801D15BC */ .word	0x00000000
/* 306880 0x801D15C0 */ .word	0x00000000
/* 306881 0x801D15C4 */ .word	0x00000000
/* 306882 0x801D15C8 */ .word	0x00000000
/* 306883 0x801D15CC */ .word	0x00000000
