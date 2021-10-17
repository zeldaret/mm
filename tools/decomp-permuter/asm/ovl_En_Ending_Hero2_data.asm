.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Ending_Hero2_InitVars
/* 000116 0x80C23400 */ .word	0x02A80400
/* 000117 0x80C23404 */ .word	0x00000009
/* 000118 0x80C23408 */ .word	0x02470000
/* 000119 0x80C2340C */ .word	0x00000280
/* 000120 0x80C23410 */ .word	EnEndingHero2_Init
/* 000121 0x80C23414 */ .word	EnEndingHero2_Destroy
/* 000122 0x80C23418 */ .word	EnEndingHero2_Update
/* 000123 0x80C2341C */ .word	EnEndingHero2_Draw
