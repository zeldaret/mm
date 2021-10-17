.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Wturn_InitVars
/* 000284 0x808A7DA0 */ .word	0x00270700
/* 000285 0x808A7DA4 */ .word	0x02100010
/* 000286 0x808A7DA8 */ .word	0x00010000
/* 000287 0x808A7DAC */ .word	0x0000014C
/* 000288 0x808A7DB0 */ .word	ObjWturn_Init
/* 000289 0x808A7DB4 */ .word	func_800BDFB0
/* 000290 0x808A7DB8 */ .word	ObjWturn_Update
/* 000291 0x808A7DBC */ .word	0x00000000
glabel D_808A7DC0
/* 000292 0x808A7DC0 */ .word	0x00000000
/* 000293 0x808A7DC4 */ .word	0xBF800000
/* 000294 0x808A7DC8 */ .word	0x00000000
/* 000295 0x808A7DCC */ .word	0x00000000
