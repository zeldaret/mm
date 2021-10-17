.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Roomtimer_InitVars
/* 000144 0x80973E90 */ .word	0x00D30500
/* 000145 0x80973E94 */ .word	0x00000010
/* 000146 0x80973E98 */ .word	0x00010000
/* 000147 0x80973E9C */ .word	0x0000014C
/* 000148 0x80973EA0 */ .word	ObjRoomtimer_Init
/* 000149 0x80973EA4 */ .word	ObjRoomtimer_Destroy
/* 000150 0x80973EA8 */ .word	ObjRoomtimer_Update
/* 000151 0x80973EAC */ .word	0x00000000
