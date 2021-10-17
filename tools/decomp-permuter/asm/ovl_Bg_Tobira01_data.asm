.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Tobira01_InitVars
/* 000244 0x80B12800 */ .word	0x01E00600
/* 000245 0x80B12804 */ .word	0x00000030
/* 000246 0x80B12808 */ .word	0x01BF0000
/* 000247 0x80B1280C */ .word	0x00000170
/* 000248 0x80B12810 */ .word	BgTobira01_Init
/* 000249 0x80B12814 */ .word	BgTobira01_Destroy
/* 000250 0x80B12818 */ .word	BgTobira01_Update
/* 000251 0x80B1281C */ .word	BgTobira01_Draw
