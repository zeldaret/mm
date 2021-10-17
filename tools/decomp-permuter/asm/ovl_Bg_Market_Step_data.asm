.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Market_Step_InitVars
/* 000036 0x80AF00F0 */ .word	0x01CC0100
/* 000037 0x80AF00F4 */ .word	0x10000020
/* 000038 0x80AF00F8 */ .word	0x01B00000
/* 000039 0x80AF00FC */ .word	0x00000144
/* 000040 0x80AF0100 */ .word	BgMarketStep_Init
/* 000041 0x80AF0104 */ .word	func_800BDFB0
/* 000042 0x80AF0108 */ .word	func_800BDFB0
/* 000043 0x80AF010C */ .word	BgMarketStep_Draw
glabel D_80AF0110
/* 000044 0x80AF0110 */ .word	0xB0FC0001
/* 000045 0x80AF0114 */ .word	0xB1000001
/* 000046 0x80AF0118 */ .word	0xB1040001
/* 000047 0x80AF011C */ .word	0x485803E8
glabel D_80AF0120
/* 000048 0x80AF0120 */ .word	0x0601F050
/* 000049 0x80AF0124 */ .word	0x06018DA0
glabel D_80AF0128
/* 000050 0x80AF0128 */ .word	0x0601EF10
/* 000051 0x80AF012C */ .word	0x06018C60
