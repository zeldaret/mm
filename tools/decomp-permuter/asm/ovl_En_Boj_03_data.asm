.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Boj_03_InitVars
/* 000016 0x809C3EE0 */ .word	0x011A0400
/* 000017 0x809C3EE4 */ .word	0x00000019
/* 000018 0x809C3EE8 */ .word	0x00010000
/* 000019 0x809C3EEC */ .word	0x0000061C
/* 000020 0x809C3EF0 */ .word	EnBoj03_Init
/* 000021 0x809C3EF4 */ .word	EnBoj03_Destroy
/* 000022 0x809C3EF8 */ .word	EnBoj03_Update
/* 000023 0x809C3EFC */ .word	EnBoj03_Draw
