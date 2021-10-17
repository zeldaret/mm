.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Ikana_Dharma_InitVars
/* 000540 0x80BECAB0 */ .word	0x02730100
/* 000541 0x80BECAB4 */ .word	0x00000010
/* 000542 0x80BECAB8 */ .word	0x02030000
/* 000543 0x80BECABC */ .word	0x000001B0
/* 000544 0x80BECAC0 */ .word	BgIkanaDharma_Init
/* 000545 0x80BECAC4 */ .word	BgIkanaDharma_Destroy
/* 000546 0x80BECAC8 */ .word	BgIkanaDharma_Update
/* 000547 0x80BECACC */ .word	BgIkanaDharma_Draw
glabel D_80BECAD0
/* 000548 0x80BECAD0 */ .word	0x0A000900
/* 000549 0x80BECAD4 */ .word	0x00010000
/* 000550 0x80BECAD8 */ .word	0x00000000
/* 000551 0x80BECADC */ .word	0x00000000
/* 000552 0x80BECAE0 */ .word	0x00000000
/* 000553 0x80BECAE4 */ .word	0x00000100
/* 000554 0x80BECAE8 */ .word	0x00000000
/* 000555 0x80BECAEC */ .word	0x00010000
/* 000556 0x80BECAF0 */ .word	0x0062000A
/* 000557 0x80BECAF4 */ .word	0x00190000
/* 000558 0x80BECAF8 */ .word	0x00000000
glabel D_80BECAFC
/* 000559 0x80BECAFC */ .word	0xB0FC0FA0
/* 000560 0x80BECB00 */ .word	0xB1000140
/* 000561 0x80BECB04 */ .word	0xB1040140
/* 000562 0x80BECB08 */ .word	0x3874FBB4
/* 000563 0x80BECB0C */ .word	0x00000000
