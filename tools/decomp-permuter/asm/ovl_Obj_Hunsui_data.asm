.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80B9DC70
/* 001544 0x80B9DC70 */ .word	0x01010100
/* 001545 0x80B9DC74 */ .word	0x02030201
/* 001546 0x80B9DC78 */ .word	0x02020200
/* 001547 0x80B9DC7C */ .word	0x03070303
/* 001548 0x80B9DC80 */ .word	0x03050301
/* 001549 0x80B9DC84 */ .word	0x03060302
/* 001550 0x80B9DC88 */ .word	0x03040300
glabel Obj_Hunsui_InitVars
/* 001551 0x80B9DC8C */ .word	0x022E0100
/* 001552 0x80B9DC90 */ .word	0x00000030
/* 001553 0x80B9DC94 */ .word	0x023D0000
/* 001554 0x80B9DC98 */ .word	0x000001B8
/* 001555 0x80B9DC9C */ .word	ObjHunsui_Init
/* 001556 0x80B9DCA0 */ .word	ObjHunsui_Destroy
/* 001557 0x80B9DCA4 */ .word	ObjHunsui_Update
/* 001558 0x80B9DCA8 */ .word	ObjHunsui_Draw
glabel D_80B9DCAC
/* 001559 0x80B9DCAC */ .word	0xC8580064
/* 001560 0x80B9DCB0 */ .word	0xB0FC0FA0
/* 001561 0x80B9DCB4 */ .word	0xB1000190
/* 001562 0x80B9DCB8 */ .word	0x31040190
/* 001563 0x80B9DCBC */ .word	0x00000000
