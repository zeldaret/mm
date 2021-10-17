.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Shutter_InitVars
/* 000144 0x80A38110 */ .word	0x01510600
/* 000145 0x80A38114 */ .word	0x00000030
/* 000146 0x80A38118 */ .word	0x016D0000
/* 000147 0x80A3811C */ .word	0x0000014C
/* 000148 0x80A38120 */ .word	ObjShutter_Init
/* 000149 0x80A38124 */ .word	ObjShutter_Destroy
/* 000150 0x80A38128 */ .word	ObjShutter_Update
/* 000151 0x80A3812C */ .word	ObjShutter_Draw
glabel D_80A38130
/* 000152 0x80A38130 */ .word	0x020A0014
/* 000153 0x80A38134 */ .word	0x00030400
/* 000154 0x80A38138 */ .word	0x02040001
/* 000155 0x80A3813C */ .word	0x00000000
