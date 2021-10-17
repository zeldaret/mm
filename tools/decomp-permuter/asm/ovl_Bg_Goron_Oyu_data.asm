.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Goron_Oyu_InitVars
/* 000440 0x80B40760 */ .word	0x01FE0100
/* 000441 0x80B40764 */ .word	0x00000030
/* 000442 0x80B40768 */ .word	0x01D30000
/* 000443 0x80B4076C */ .word	0x00000180
/* 000444 0x80B40770 */ .word	BgGoronOyu_Init
/* 000445 0x80B40774 */ .word	BgGoronOyu_Destroy
/* 000446 0x80B40778 */ .word	BgGoronOyu_Update
/* 000447 0x80B4077C */ .word	BgGoronOyu_Draw
glabel D_80B40780
/* 000448 0x80B40780 */ .word	0x00000000
/* 000449 0x80B40784 */ .word	0x00000000
/* 000450 0x80B40788 */ .word	0x00000000
/* 000451 0x80B4078C */ .word	0x00000000
