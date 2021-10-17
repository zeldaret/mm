.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Dowsing_InitVars
/* 000076 0x80B23E80 */ .word	0x01EC0700
/* 000077 0x80B23E84 */ .word	0x00000010
/* 000078 0x80B23E88 */ .word	0x00010000
/* 000079 0x80B23E8C */ .word	0x00000144
/* 000080 0x80B23E90 */ .word	ObjDowsing_Init
/* 000081 0x80B23E94 */ .word	ObjDowsing_Destroy
/* 000082 0x80B23E98 */ .word	ObjDowsing_Update
/* 000083 0x80B23E9C */ .word	0x00000000
