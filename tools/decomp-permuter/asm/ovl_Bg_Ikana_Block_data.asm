.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Ikana_Block_InitVars
/* 000752 0x80B7F620 */ .word	0x02180100
/* 000753 0x80B7F624 */ .word	0x00000010
/* 000754 0x80B7F628 */ .word	0x00030000
/* 000755 0x80B7F62C */ .word	0x00000180
/* 000756 0x80B7F630 */ .word	BgIkanaBlock_Init
/* 000757 0x80B7F634 */ .word	BgIkanaBlock_Destroy
/* 000758 0x80B7F638 */ .word	BgIkanaBlock_Update
/* 000759 0x80B7F63C */ .word	0x00000000
glabel D_80B7F640
/* 000760 0x80B7F640 */ .word	0xB0FC0FA0
/* 000761 0x80B7F644 */ .word	0xB10000FA
/* 000762 0x80B7F648 */ .word	0xB10400FA
/* 000763 0x80B7F64C */ .word	0x48580064
