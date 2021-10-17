.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Nwc_InitVars
/* 001124 0x80945370 */ .word	0x009D0600
/* 001125 0x80945374 */ .word	0x00000010
/* 001126 0x80945378 */ .word	0x00F20000
/* 001127 0x8094537C */ .word	0x00000268
/* 001128 0x80945380 */ .word	EnNwc_Init
/* 001129 0x80945384 */ .word	EnNwc_Destroy
/* 001130 0x80945388 */ .word	EnNwc_Update
/* 001131 0x8094538C */ .word	EnNwc_Draw
glabel D_80945390
/* 001132 0x80945390 */ .word	0xFFFFFFFF
glabel D_80945394
/* 001133 0x80945394 */ .word	0x505050FF
glabel D_80945398
/* 001134 0x80945398 */ .word	0x060007D0
/* 001135 0x8094539C */ .word	0x060009D0
