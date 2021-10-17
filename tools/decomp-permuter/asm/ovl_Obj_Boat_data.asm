.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Boat_InitVars
/* 000452 0x80B9B660 */ .word	0x022C0100
/* 000453 0x80B9B664 */ .word	0x00000010
/* 000454 0x80B9B668 */ .word	0x020E0000
/* 000455 0x80B9B66C */ .word	0x00000168
/* 000456 0x80B9B670 */ .word	ObjBoat_Init
/* 000457 0x80B9B674 */ .word	ObjBoat_Destroy
/* 000458 0x80B9B678 */ .word	ObjBoat_Update
/* 000459 0x80B9B67C */ .word	ObjBoat_Draw
glabel D_80B9B680
/* 000460 0x80B9B680 */ .word	0xC8580064
/* 000461 0x80B9B684 */ .word	0xB0FC0FA0
/* 000462 0x80B9B688 */ .word	0xB10003E8
/* 000463 0x80B9B68C */ .word	0x310403E8
