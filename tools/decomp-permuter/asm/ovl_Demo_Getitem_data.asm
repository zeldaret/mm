.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Demo_Getitem_InitVars
/* 000192 0x80A4FD40 */ .word	0x01650100
/* 000193 0x80A4FD44 */ .word	0x00000030
/* 000194 0x80A4FD48 */ .word	0x00010000
/* 000195 0x80A4FD4C */ .word	0x00000150
/* 000196 0x80A4FD50 */ .word	DemoGetitem_Init
/* 000197 0x80A4FD54 */ .word	DemoGetitem_Destroy
/* 000198 0x80A4FD58 */ .word	DemoGetitem_Update
/* 000199 0x80A4FD5C */ .word	0x00000000
glabel D_80A4FD60
/* 000200 0x80A4FD60 */ .word	0x020A01FB
glabel D_80A4FD64
/* 000201 0x80A4FD64 */ .word	0x006A0068
glabel D_80A4FD68
/* 000202 0x80A4FD68 */ .word	0x006E0236
/* 000203 0x80A4FD6C */ .word	0x00000000
