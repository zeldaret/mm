.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Encount1_InitVars
/* 000360 0x808E0DD0 */ .word	0x005B0600
/* 000361 0x808E0DD4 */ .word	0x08100010
/* 000362 0x808E0DD8 */ .word	0x00010000
/* 000363 0x808E0DDC */ .word	0x00000164
/* 000364 0x808E0DE0 */ .word	EnEncount1_Init
/* 000365 0x808E0DE4 */ .word	0x00000000
/* 000366 0x808E0DE8 */ .word	EnEncount1_Update
/* 000367 0x808E0DEC */ .word	0x00000000
glabel D_808E0DF0
/* 000368 0x808E0DF0 */ .word	0x0109000A
/* 000369 0x808E0DF4 */ .word	0x01800180
glabel D_808E0DF8
/* 000370 0x808E0DF8 */ .word	0x00010000
/* 000371 0x808E0DFC */ .word	0x00010003
