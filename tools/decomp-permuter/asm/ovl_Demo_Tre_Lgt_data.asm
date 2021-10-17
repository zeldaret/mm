.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_808E1490
/* 000404 0x808E1490 */ .word	0x3F800000
/* 000405 0x808E1494 */ .word	0x43080000
/* 000406 0x808E1498 */ .word	0x433E0000
/* 000407 0x808E149C */ .word	0x42200000
/* 000408 0x808E14A0 */ .word	0x3F800000
/* 000409 0x808E14A4 */ .word	0x43080000
/* 000410 0x808E14A8 */ .word	0x435C0000
/* 000411 0x808E14AC */ .word	0x42480000
glabel Demo_Tre_Lgt_InitVars
/* 000412 0x808E14B0 */ .word	0x005C0700
/* 000413 0x808E14B4 */ .word	0x00000010
/* 000414 0x808E14B8 */ .word	0x000C0000
/* 000415 0x808E14BC */ .word	0x00000178
/* 000416 0x808E14C0 */ .word	DemoTreLgt_Init
/* 000417 0x808E14C4 */ .word	DemoTreLgt_Destroy
/* 000418 0x808E14C8 */ .word	DemoTreLgt_Update
/* 000419 0x808E14CC */ .word	DemoTreLgt_Draw
glabel D_808E14D0
/* 000420 0x808E14D0 */ .word	0x06006A20
/* 000421 0x808E14D4 */ .word	0x06006E30
glabel D_808E14D8
/* 000422 0x808E14D8 */ .word	func_808E0EF4
/* 000423 0x808E14DC */ .word	func_808E0FE0
