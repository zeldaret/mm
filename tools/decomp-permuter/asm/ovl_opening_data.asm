.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel openingEntrances
/* 000116 0x80803FC0 */ .word	0x00001C00
/* 000117 0x80803FC4 */ .word	0x00001C10
glabel openingCutscenes
/* 000118 0x80803FC8 */ .word	0x0000FFFA
/* 000119 0x80803FCC */ .word	0x0000FFFA
