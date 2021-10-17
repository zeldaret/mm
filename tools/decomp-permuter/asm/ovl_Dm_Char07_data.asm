.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Dm_Char07_InitVars
/* 000396 0x80AAEFF0 */ .word	0x01990700
/* 000397 0x80AAEFF4 */ .word	0x00000030
/* 000398 0x80AAEFF8 */ .word	0x02120000
/* 000399 0x80AAEFFC */ .word	0x000002BC
/* 000400 0x80AAF000 */ .word	DmChar07_Init
/* 000401 0x80AAF004 */ .word	DmChar07_Destroy
/* 000402 0x80AAF008 */ .word	DmChar07_Update
/* 000403 0x80AAF00C */ .word	DmChar07_Draw
