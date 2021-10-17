.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_F40_Switch_InitVars
/* 000392 0x80BC4DD0 */ .word	0x02460000
/* 000393 0x80BC4DD4 */ .word	0x00000010
/* 000394 0x80BC4DD8 */ .word	0x02220000
/* 000395 0x80BC4DDC */ .word	0x00000168
/* 000396 0x80BC4DE0 */ .word	BgF40Switch_Init
/* 000397 0x80BC4DE4 */ .word	BgF40Switch_Destroy
/* 000398 0x80BC4DE8 */ .word	BgF40Switch_Update
/* 000399 0x80BC4DEC */ .word	BgF40Switch_Draw
glabel D_80BC4DF0
/* 000400 0x80BC4DF0 */ .word	0x00000000
glabel D_80BC4DF4
/* 000401 0x80BC4DF4 */ .word	0x00000000
/* 000402 0x80BC4DF8 */ .word	0x00000000
/* 000403 0x80BC4DFC */ .word	0x00000000
/* 000404 0x80BC4E00 */ .word	0x00000000
glabel D_80BC4E04
/* 000405 0x80BC4E04 */ .word	0xB0FC0FA0
/* 000406 0x80BC4E08 */ .word	0xB10000C8
/* 000407 0x80BC4E0C */ .word	0xB10400C8
/* 000408 0x80BC4E10 */ .word	0x4858007B
/* 000409 0x80BC4E14 */ .word	0x00000000
/* 000410 0x80BC4E18 */ .word	0x00000000
/* 000411 0x80BC4E1C */ .word	0x00000000
