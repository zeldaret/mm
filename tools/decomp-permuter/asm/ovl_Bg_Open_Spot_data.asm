.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Open_Spot_InitVars
/* 000108 0x80ACB390 */ .word	0x01AD0600
/* 000109 0x80ACB394 */ .word	0x00000010
/* 000110 0x80ACB398 */ .word	0x019F0000
/* 000111 0x80ACB39C */ .word	0x00000148
/* 000112 0x80ACB3A0 */ .word	BgOpenSpot_Init
/* 000113 0x80ACB3A4 */ .word	BgOpenSpot_Destroy
/* 000114 0x80ACB3A8 */ .word	BgOpenSpot_Update
/* 000115 0x80ACB3AC */ .word	0x00000000
glabel D_80ACB3B0
/* 000116 0x80ACB3B0 */ .word	0xB0FC0FA0
/* 000117 0x80ACB3B4 */ .word	0xB1000230
/* 000118 0x80ACB3B8 */ .word	0xB1040320
/* 000119 0x80ACB3BC */ .word	0x48580064
