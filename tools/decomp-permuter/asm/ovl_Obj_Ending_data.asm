.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Obj_Ending_InitVars
/* 000064 0x80C25CC0 */ .word	0x02B00100
/* 000065 0x80C25CC4 */ .word	0x00000030
/* 000066 0x80C25CC8 */ .word	0x02810000
/* 000067 0x80C25CCC */ .word	0x0000014C
/* 000068 0x80C25CD0 */ .word	ObjEnding_Init
/* 000069 0x80C25CD4 */ .word	func_800BDFB0
/* 000070 0x80C25CD8 */ .word	ObjEnding_Update
/* 000071 0x80C25CDC */ .word	ObjEnding_Draw
glabel D_80C25CE0
/* 000072 0x80C25CE0 */ .word	0x06003440
/* 000073 0x80C25CE4 */ .word	0x060031A0
/* 000074 0x80C25CE8 */ .word	0x00000000
/* 000075 0x80C25CEC */ .word	0x00000000
/* 000076 0x80C25CF0 */ .word	0x060003D0
/* 000077 0x80C25CF4 */ .word	0x06001FF8
glabel D_80C25CF8
/* 000078 0x80C25CF8 */ .word	0x48580064
/* 000079 0x80C25CFC */ .word	0x00000000
