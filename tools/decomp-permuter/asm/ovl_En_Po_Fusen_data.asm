.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Po_Fusen_InitVars
/* 000708 0x80AC1D80 */ .word	0x01A60600
/* 000709 0x80AC1D84 */ .word	0x80100030
/* 000710 0x80AC1D88 */ .word	0x019B0000
/* 000711 0x80AC1D8C */ .word	0x00000274
/* 000712 0x80AC1D90 */ .word	EnPoFusen_Init
/* 000713 0x80AC1D94 */ .word	EnPoFusen_Destroy
/* 000714 0x80AC1D98 */ .word	EnPoFusen_Update
/* 000715 0x80AC1D9C */ .word	EnPoFusen_Draw
glabel D_80AC1DA0
/* 000716 0x80AC1DA0 */ .word	0x0A000939
/* 000717 0x80AC1DA4 */ .word	0x12040000
/* 000718 0x80AC1DA8 */ .word	0x00000000
/* 000719 0x80AC1DAC */ .word	0xF7CFFFFF
/* 000720 0x80AC1DB0 */ .word	0x00000000
/* 000721 0x80AC1DB4 */ .word	0xF7CFFFFF
/* 000722 0x80AC1DB8 */ .word	0x00000000
/* 000723 0x80AC1DBC */ .word	0x00010100
/* 000724 0x80AC1DC0 */ .word	0x00000000
/* 000725 0x80AC1DC4 */ .word	0x00000000
/* 000726 0x80AC1DC8 */ .word	0x00C80064
glabel D_80AC1DCC
/* 000727 0x80AC1DCC */ .word	0x00000000
/* 000728 0x80AC1DD0 */ .word	0x00F10000
/* 000729 0x80AC1DD4 */ .word	0x000000F1
/* 000730 0x80AC1DD8 */ .word	0xF1F1F100
/* 000731 0x80AC1DDC */ .word	0x00000000
/* 000732 0x80AC1DE0 */ .word	0x00000000
/* 000733 0x80AC1DE4 */ .word	0x00000000
/* 000734 0x80AC1DE8 */ .word	0x00000000
/* 000735 0x80AC1DEC */ .word	0x00000000
