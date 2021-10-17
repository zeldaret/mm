.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Zl1_InitVars
/* 000016 0x8089EDD0 */ .word	0x001B0400
/* 000017 0x8089EDD4 */ .word	0x00000019
/* 000018 0x8089EDD8 */ .word	0x00190000
/* 000019 0x8089EDDC */ .word	0x00000204
/* 000020 0x8089EDE0 */ .word	EnZl1_Init
/* 000021 0x8089EDE4 */ .word	EnZl1_Destroy
/* 000022 0x8089EDE8 */ .word	EnZl1_Update
/* 000023 0x8089EDEC */ .word	EnZl1_Draw
