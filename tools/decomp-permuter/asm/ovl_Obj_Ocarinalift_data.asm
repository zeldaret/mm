.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Ocarinalift_InitVars
/* 000548 0x80AC9D50 */ .word	0x01AA0100
/* 000549 0x80AC9D54 */ .word	0x00000010
/* 000550 0x80AC9D58 */ .word	0x01630000
/* 000551 0x80AC9D5C */ .word	0x00000178
/* 000552 0x80AC9D60 */ .word	ObjOcarinalift_Init
/* 000553 0x80AC9D64 */ .word	ObjOcarinalift_Destroy
/* 000554 0x80AC9D68 */ .word	ObjOcarinalift_Update
/* 000555 0x80AC9D6C */ .word	ObjOcarinalift_Draw
glabel D_80AC9D70
/* 000556 0x80AC9D70 */ .word	0x801F0002
/* 000557 0x80AC9D74 */ .word	0xB0FC0FA0
/* 000558 0x80AC9D78 */ .word	0xB10000C8
/* 000559 0x80AC9D7C */ .word	0xB104012C
/* 000560 0x80AC9D80 */ .word	0x48580064
/* 000561 0x80AC9D84 */ .word	0x00000000
/* 000562 0x80AC9D88 */ .word	0x00000000
/* 000563 0x80AC9D8C */ .word	0x00000000
