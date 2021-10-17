.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Boj_04_InitVars
/* 000016 0x809CB240 */ .word	0x01210400
/* 000017 0x809CB244 */ .word	0x00000019
/* 000018 0x809CB248 */ .word	0x00010000
/* 000019 0x809CB24C */ .word	0x0000061C
/* 000020 0x809CB250 */ .word	EnBoj04_Init
/* 000021 0x809CB254 */ .word	EnBoj04_Destroy
/* 000022 0x809CB258 */ .word	EnBoj04_Update
/* 000023 0x809CB25C */ .word	EnBoj04_Draw
