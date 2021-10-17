.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_HsStump_InitVars
/* 000332 0x80BDAF60 */ .word	0x025E0100
/* 000333 0x80BDAF64 */ .word	0x00000010
/* 000334 0x80BDAF68 */ .word	0x02390000
/* 000335 0x80BDAF6C */ .word	0x0000016C
/* 000336 0x80BDAF70 */ .word	ObjHsStump_Init
/* 000337 0x80BDAF74 */ .word	ObjHsStump_Destroy
/* 000338 0x80BDAF78 */ .word	ObjHsStump_Update
/* 000339 0x80BDAF7C */ .word	ObjHsStump_Draw
glabel D_80BDAF80
/* 000340 0x80BDAF80 */ .word	0x485800B4
glabel D_80BDAF84
/* 000341 0x80BDAF84 */ .word	0x00000000
/* 000342 0x80BDAF88 */ .word	0x00000000
/* 000343 0x80BDAF8C */ .word	0x00000000
