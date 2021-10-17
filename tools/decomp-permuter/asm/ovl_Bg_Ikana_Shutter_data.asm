.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Ikana_Shutter_InitVars
/* 000408 0x80BD5CF0 */ .word	0x02570000
/* 000409 0x80BD5CF4 */ .word	0x00000010
/* 000410 0x80BD5CF8 */ .word	0x02030000
/* 000411 0x80BD5CFC */ .word	0x00000160
/* 000412 0x80BD5D00 */ .word	BgIkanaShutter_Init
/* 000413 0x80BD5D04 */ .word	BgIkanaShutter_Destroy
/* 000414 0x80BD5D08 */ .word	BgIkanaShutter_Update
/* 000415 0x80BD5D0C */ .word	BgIkanaShutter_Draw
glabel D_80BD5D10
/* 000416 0x80BD5D10 */ .word	0xB0FC0FA0
/* 000417 0x80BD5D14 */ .word	0xB10001F4
/* 000418 0x80BD5D18 */ .word	0xB10401F4
/* 000419 0x80BD5D1C */ .word	0x48580064
