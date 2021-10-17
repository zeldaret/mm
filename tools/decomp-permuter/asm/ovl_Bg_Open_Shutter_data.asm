.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Open_Shutter_InitVars
/* 000388 0x80ACB120 */ .word	0x01AC0A00
/* 000389 0x80ACB124 */ .word	0x00000010
/* 000390 0x80ACB128 */ .word	0x019F0000
/* 000391 0x80ACB12C */ .word	0x00000168
/* 000392 0x80ACB130 */ .word	BgOpenShutter_Init
/* 000393 0x80ACB134 */ .word	BgOpenShutter_Destroy
/* 000394 0x80ACB138 */ .word	BgOpenShutter_Update
/* 000395 0x80ACB13C */ .word	BgOpenShutter_Draw
glabel D_80ACB140
/* 000396 0x80ACB140 */ .word	0xB0FC0FA0
/* 000397 0x80ACB144 */ .word	0xB100015E
/* 000398 0x80ACB148 */ .word	0xB104015E
/* 000399 0x80ACB14C */ .word	0x48580064
