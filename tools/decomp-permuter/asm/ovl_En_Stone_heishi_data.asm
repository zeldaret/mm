.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Stone_heishi_InitVars
/* 001092 0x80BCA380 */ .word	0x024A0400
/* 001093 0x80BCA384 */ .word	0x00000089
/* 001094 0x80BCA388 */ .word	0x01B60000
/* 001095 0x80BCA38C */ .word	0x000002C4
/* 001096 0x80BCA390 */ .word	EnStoneheishi_Init
/* 001097 0x80BCA394 */ .word	EnStoneheishi_Destroy
/* 001098 0x80BCA398 */ .word	EnStoneheishi_Update
/* 001099 0x80BCA39C */ .word	EnStoneheishi_Draw
glabel D_80BCA3A0
/* 001100 0x80BCA3A0 */ .word	0x0A000039
/* 001101 0x80BCA3A4 */ .word	0x20010000
/* 001102 0x80BCA3A8 */ .word	0x00000000
/* 001103 0x80BCA3AC */ .word	0x00000000
/* 001104 0x80BCA3B0 */ .word	0x00000000
/* 001105 0x80BCA3B4 */ .word	0xF7CFFFFF
/* 001106 0x80BCA3B8 */ .word	0x00000000
/* 001107 0x80BCA3BC */ .word	0x00000100
/* 001108 0x80BCA3C0 */ .word	0x000F0046
/* 001109 0x80BCA3C4 */ .word	0x00000000
/* 001110 0x80BCA3C8 */ .word	0x00000000
glabel D_80BCA3CC
/* 001111 0x80BCA3CC */ .word	0x14731474
/* 001112 0x80BCA3D0 */ .word	0x14751476
/* 001113 0x80BCA3D4 */ .word	0x14771478
/* 001114 0x80BCA3D8 */ .word	0x1479147A
/* 001115 0x80BCA3DC */ .word	0x14720000
glabel D_80BCA3E0
/* 001116 0x80BCA3E0 */ .word	0x06006C18
/* 001117 0x80BCA3E4 */ .word	0x060020D8
/* 001118 0x80BCA3E8 */ .word	0x06002A84
/* 001119 0x80BCA3EC */ .word	0x06003BFC
/* 001120 0x80BCA3F0 */ .word	0x06003380
glabel D_80BCA3F4
/* 001121 0x80BCA3F4 */ .word	0x060020D8
/* 001122 0x80BCA3F8 */ .word	0x06004770
glabel D_80BCA3FC
/* 001123 0x80BCA3FC */ .word	0x00020000
/* 001124 0x80BCA400 */ .word	0x00000200
glabel D_80BCA404
/* 001125 0x80BCA404 */ .word	0x00000000
glabel D_80BCA408
/* 001126 0x80BCA408 */ .word	0x00000000
glabel D_80BCA40C
/* 001127 0x80BCA40C */ .word	0x00000000
