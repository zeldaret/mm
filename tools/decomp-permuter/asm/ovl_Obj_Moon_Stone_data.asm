.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Moon_Stone_InitVars
/* 000320 0x80C06A10 */ .word	0x02830600
/* 000321 0x80C06A14 */ .word	0x00100010
/* 000322 0x80C06A18 */ .word	0x01B10000
/* 000323 0x80C06A1C */ .word	0x00000198
/* 000324 0x80C06A20 */ .word	ObjMoonStone_Init
/* 000325 0x80C06A24 */ .word	ObjMoonStone_Destroy
/* 000326 0x80C06A28 */ .word	ObjMoonStone_Update
/* 000327 0x80C06A2C */ .word	ObjMoonStone_Draw
