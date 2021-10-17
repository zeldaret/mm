.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Danpeilift_InitVars
/* 000472 0x80C1B520 */ .word	0x029B0100
/* 000473 0x80C1B524 */ .word	0x00000010
/* 000474 0x80C1B528 */ .word	0x02730000
/* 000475 0x80C1B52C */ .word	0x0000018C
/* 000476 0x80C1B530 */ .word	ObjDanpeilift_Init
/* 000477 0x80C1B534 */ .word	ObjDanpeilift_Destroy
/* 000478 0x80C1B538 */ .word	ObjDanpeilift_Update
/* 000479 0x80C1B53C */ .word	ObjDanpeilift_Draw
glabel D_80C1B540
/* 000480 0x80C1B540 */ .word	0xB0FC0FA0
/* 000481 0x80C1B544 */ .word	0xB10000C8
/* 000482 0x80C1B548 */ .word	0xB1040190
/* 000483 0x80C1B54C */ .word	0x48580064
