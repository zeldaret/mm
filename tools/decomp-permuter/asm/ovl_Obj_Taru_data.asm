.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Taru_InitVars
/* 000784 0x80B9C320 */ .word	0x022D0100
/* 000785 0x80B9C324 */ .word	0x00000000
/* 000786 0x80B9C328 */ .word	0x02500000
/* 000787 0x80B9C32C */ .word	0x000001B0
/* 000788 0x80B9C330 */ .word	ObjTaru_Init
/* 000789 0x80B9C334 */ .word	ObjTaru_Destroy
/* 000790 0x80B9C338 */ .word	ObjTaru_Update
/* 000791 0x80B9C33C */ .word	ObjTaru_Draw
glabel D_80B9C340
/* 000792 0x80B9C340 */ .word	0x0A000900
/* 000793 0x80B9C344 */ .word	0x20010000
/* 000794 0x80B9C348 */ .word	0x00000000
/* 000795 0x80B9C34C */ .word	0x00000000
/* 000796 0x80B9C350 */ .word	0x00000000
/* 000797 0x80B9C354 */ .word	0x80000508
/* 000798 0x80B9C358 */ .word	0x00000000
/* 000799 0x80B9C35C */ .word	0x00010000
/* 000800 0x80B9C360 */ .word	0x001E0032
/* 000801 0x80B9C364 */ .word	0x00000000
/* 000802 0x80B9C368 */ .word	0x00000000
glabel D_80B9C36C
/* 000803 0x80B9C36C */ .word	0xC8580064
/* 000804 0x80B9C370 */ .word	0xB0FC0CE4
/* 000805 0x80B9C374 */ .word	0xB10000C8
/* 000806 0x80B9C378 */ .word	0x310400C8
/* 000807 0x80B9C37C */ .word	0x00000000
