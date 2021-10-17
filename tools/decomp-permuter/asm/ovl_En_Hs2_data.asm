.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Hs2_InitVars
/* 000036 0x8098EFF0 */ .word	0x00E70400
/* 000037 0x8098EFF4 */ .word	0x00000009
/* 000038 0x8098EFF8 */ .word	0x00010000
/* 000039 0x8098EFFC */ .word	0x00000398
/* 000040 0x8098F000 */ .word	EnHs2_Init
/* 000041 0x8098F004 */ .word	EnHs2_Destroy
/* 000042 0x8098F008 */ .word	EnHs2_Update
/* 000043 0x8098F00C */ .word	EnHs2_Draw
