.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Ending_Hero3_InitVars
/* 000116 0x80C23630 */ .word	0x02A90400
/* 000117 0x80C23634 */ .word	0x00000009
/* 000118 0x80C23638 */ .word	0x00F00000
/* 000119 0x80C2363C */ .word	0x0000025C
/* 000120 0x80C23640 */ .word	EnEndingHero3_Init
/* 000121 0x80C23644 */ .word	EnEndingHero3_Destroy
/* 000122 0x80C23648 */ .word	EnEndingHero3_Update
/* 000123 0x80C2364C */ .word	EnEndingHero3_Draw
