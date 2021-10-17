.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Torch_InitVars
/* 000036 0x809735E0 */ .word	0x00CE0700
/* 000037 0x809735E4 */ .word	0x00000000
/* 000038 0x809735E8 */ .word	0x00010000
/* 000039 0x809735EC */ .word	0x00000144
/* 000040 0x809735F0 */ .word	EnTorch_Init
/* 000041 0x809735F4 */ .word	0x00000000
/* 000042 0x809735F8 */ .word	0x00000000
/* 000043 0x809735FC */ .word	0x00000000
glabel D_80973600
/* 000044 0x80973600 */ .word	0x02040506
/* 000045 0x80973604 */ .word	0x363A1414
/* 000046 0x80973608 */ .word	0x00000000
/* 000047 0x8097360C */ .word	0x00000000
