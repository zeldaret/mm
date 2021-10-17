.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_River_Sound_InitVars
/* 000132 0x808A8040 */ .word	0x00280700
/* 000133 0x808A8044 */ .word	0x00000030
/* 000134 0x808A8048 */ .word	0x00010000
/* 000135 0x808A804C */ .word	0x0000014C
/* 000136 0x808A8050 */ .word	EnRiverSound_Init
/* 000137 0x808A8054 */ .word	func_800BDFB0
/* 000138 0x808A8058 */ .word	EnRiverSound_Update
/* 000139 0x808A805C */ .word	EnRiverSound_Draw
glabel D_808A8060
/* 000140 0x808A8060 */ .word	0x3F333333
/* 000141 0x808A8064 */ .word	0x3F800000
/* 000142 0x808A8068 */ .word	0x3FB33333
/* 000143 0x808A806C */ .word	0x00000000
