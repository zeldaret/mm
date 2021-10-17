.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Boj_05_InitVars
/* 000016 0x80A0C7C0 */ .word	0x01320400
/* 000017 0x80A0C7C4 */ .word	0x00000019
/* 000018 0x80A0C7C8 */ .word	0x00010000
/* 000019 0x80A0C7CC */ .word	0x0000061C
/* 000020 0x80A0C7D0 */ .word	EnBoj05_Init
/* 000021 0x80A0C7D4 */ .word	EnBoj05_Destroy
/* 000022 0x80A0C7D8 */ .word	EnBoj05_Update
/* 000023 0x80A0C7DC */ .word	EnBoj05_Draw
