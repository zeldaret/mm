.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Okarina_Effect_InitVars
/* 000124 0x8096B290 */ .word	0x00C40700
/* 000125 0x8096B294 */ .word	0x02000010
/* 000126 0x8096B298 */ .word	0x00010000
/* 000127 0x8096B29C */ .word	0x0000014C
/* 000128 0x8096B2A0 */ .word	EnOkarinaEffect_Init
/* 000129 0x8096B2A4 */ .word	EnOkarinaEffect_Destroy
/* 000130 0x8096B2A8 */ .word	EnOkarinaEffect_Update
/* 000131 0x8096B2AC */ .word	0x00000000
