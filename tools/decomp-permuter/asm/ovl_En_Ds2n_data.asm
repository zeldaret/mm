.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Ds2n_InitVars
/* 000280 0x80AE1AB0 */ .word	0x01C30400
/* 000281 0x80AE1AB4 */ .word	0x02000019
/* 000282 0x80AE1AB8 */ .word	0x01AA0000
/* 000283 0x80AE1ABC */ .word	0x00000234
/* 000284 0x80AE1AC0 */ .word	EnDs2n_Init
/* 000285 0x80AE1AC4 */ .word	EnDs2n_Destroy
/* 000286 0x80AE1AC8 */ .word	EnDs2n_Update
/* 000287 0x80AE1ACC */ .word	EnDs2n_Draw
glabel D_80AE1AD0
/* 000288 0x80AE1AD0 */ .word	0x06008038
/* 000289 0x80AE1AD4 */ .word	0x3F800000
/* 000290 0x80AE1AD8 */ .word	0x00000000
/* 000291 0x80AE1ADC */ .word	0x00000000
/* 000292 0x80AE1AE0 */ .word	0x00000000
/* 000293 0x80AE1AE4 */ .word	0x00000000
glabel D_80AE1AE8
/* 000294 0x80AE1AE8 */ .word	0x00000000
/* 000295 0x80AE1AEC */ .word	0x00000000
/* 000296 0x80AE1AF0 */ .word	0x00000000
glabel D_80AE1AF4
/* 000297 0x80AE1AF4 */ .word	0x06005E18
/* 000298 0x80AE1AF8 */ .word	0x06004CD8
/* 000299 0x80AE1AFC */ .word	0x060050D8
