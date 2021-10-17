.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Firefly2_InitVars
/* 000016 0x80A56100 */ .word	0x016E0500
/* 000017 0x80A56104 */ .word	0x00005015
/* 000018 0x80A56108 */ .word	0x000B0000
/* 000019 0x80A5610C */ .word	0x0000036C
/* 000020 0x80A56110 */ .word	EnFirefly2_Init
/* 000021 0x80A56114 */ .word	EnFirefly2_Destroy
/* 000022 0x80A56118 */ .word	EnFirefly2_Update
/* 000023 0x80A5611C */ .word	EnFirefly2_Draw
