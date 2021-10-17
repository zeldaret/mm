.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Fu_Mizu_InitVars
/* 000164 0x80ADAD80 */ .word	0x01BC0100
/* 000165 0x80ADAD84 */ .word	0x00000030
/* 000166 0x80ADAD88 */ .word	0x01A00000
/* 000167 0x80ADAD8C */ .word	0x00000164
/* 000168 0x80ADAD90 */ .word	BgFuMizu_Init
/* 000169 0x80ADAD94 */ .word	BgFuMizu_Destroy
/* 000170 0x80ADAD98 */ .word	BgFuMizu_Update
/* 000171 0x80ADAD9C */ .word	BgFuMizu_Draw
