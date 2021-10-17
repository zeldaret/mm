.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Stream_InitVars
/* 000300 0x80965B00 */ .word	0x00B80100
/* 000301 0x80965B04 */ .word	0x00000010
/* 000302 0x80965B08 */ .word	0x01060000
/* 000303 0x80965B0C */ .word	0x00000150
/* 000304 0x80965B10 */ .word	EnStream_Init
/* 000305 0x80965B14 */ .word	EnStream_Destroy
/* 000306 0x80965B18 */ .word	EnStream_Update
/* 000307 0x80965B1C */ .word	EnStream_Draw
glabel D_80965B20
/* 000308 0x80965B20 */ .word	0x48580014
/* 000309 0x80965B24 */ .word	0x00000000
/* 000310 0x80965B28 */ .word	0x00000000
/* 000311 0x80965B2C */ .word	0x00000000
