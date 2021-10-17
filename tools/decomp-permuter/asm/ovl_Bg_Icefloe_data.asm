.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Icefloe_InitVars
/* 000392 0x80AC4F10 */ .word	0x01A90100
/* 000393 0x80AC4F14 */ .word	0x00000010
/* 000394 0x80AC4F18 */ .word	0x01E70000
/* 000395 0x80AC4F1C */ .word	0x00000164
/* 000396 0x80AC4F20 */ .word	BgIcefloe_Init
/* 000397 0x80AC4F24 */ .word	BgIcefloe_Destroy
/* 000398 0x80AC4F28 */ .word	BgIcefloe_Update
/* 000399 0x80AC4F2C */ .word	BgIcefloe_Draw
glabel D_80AC4F30
/* 000400 0x80AC4F30 */ .word	0x00000000
/* 000401 0x80AC4F34 */ .word	0x00000000
glabel D_80AC4F38
/* 000402 0x80AC4F38 */ .word	0x00000000
glabel D_80AC4F3C
/* 000403 0x80AC4F3C */ .word	0x48580000
glabel D_80AC4F40
/* 000404 0x80AC4F40 */ .word	0x00000000
/* 000405 0x80AC4F44 */ .word	0xBF000000
/* 000406 0x80AC4F48 */ .word	0x00000000
/* 000407 0x80AC4F4C */ .word	0x00000000
