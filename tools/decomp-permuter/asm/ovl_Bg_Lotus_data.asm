.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Lotus_InitVars
/* 000356 0x80AD6CF0 */ .word	0x01B90100
/* 000357 0x80AD6CF4 */ .word	0x00000000
/* 000358 0x80AD6CF8 */ .word	0x01A50000
/* 000359 0x80AD6CFC */ .word	0x0000016C
/* 000360 0x80AD6D00 */ .word	BgLotus_Init
/* 000361 0x80AD6D04 */ .word	BgLotus_Destroy
/* 000362 0x80AD6D08 */ .word	BgLotus_Update
/* 000363 0x80AD6D0C */ .word	BgLotus_Draw
glabel D_80AD6D10
/* 000364 0x80AD6D10 */ .word	0x48580064
/* 000365 0x80AD6D14 */ .word	0x00000000
/* 000366 0x80AD6D18 */ .word	0x00000000
/* 000367 0x80AD6D1C */ .word	0x00000000
