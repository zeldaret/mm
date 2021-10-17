.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Kibako2_InitVars
/* 000544 0x8098EE40 */ .word	0x00E50100
/* 000545 0x8098EE44 */ .word	0x00000000
/* 000546 0x8098EE48 */ .word	0x01330000
/* 000547 0x8098EE4C */ .word	0x000001B0
/* 000548 0x8098EE50 */ .word	ObjKibako2_Init
/* 000549 0x8098EE54 */ .word	ObjKibako2_Destroy
/* 000550 0x8098EE58 */ .word	ObjKibako2_Update
/* 000551 0x8098EE5C */ .word	ObjKibako2_Draw
glabel D_8098EE60
/* 000552 0x8098EE60 */ .word	0x0A000900
/* 000553 0x8098EE64 */ .word	0x20010000
/* 000554 0x8098EE68 */ .word	0x00000000
/* 000555 0x8098EE6C */ .word	0x00000000
/* 000556 0x8098EE70 */ .word	0x00000000
/* 000557 0x8098EE74 */ .word	0x80000508
/* 000558 0x8098EE78 */ .word	0x00000000
/* 000559 0x8098EE7C */ .word	0x00010000
/* 000560 0x8098EE80 */ .word	0x001F0030
/* 000561 0x8098EE84 */ .word	0x00000000
/* 000562 0x8098EE88 */ .word	0x00000000
glabel D_8098EE8C
/* 000563 0x8098EE8C */ .word	0xC8580064
/* 000564 0x8098EE90 */ .word	0xB0FC07D0
/* 000565 0x8098EE94 */ .word	0xB10000C8
/* 000566 0x8098EE98 */ .word	0x310400C8
/* 000567 0x8098EE9C */ .word	0x00000000
