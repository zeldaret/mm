.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Boj_02_InitVars
/* 000016 0x809C3E50 */ .word	0x01190400
/* 000017 0x809C3E54 */ .word	0x00000019
/* 000018 0x809C3E58 */ .word	0x00010000
/* 000019 0x809C3E5C */ .word	0x0000061C
/* 000020 0x809C3E60 */ .word	EnBoj02_Init
/* 000021 0x809C3E64 */ .word	EnBoj02_Destroy
/* 000022 0x809C3E68 */ .word	EnBoj02_Update
/* 000023 0x809C3E6C */ .word	EnBoj02_Draw
