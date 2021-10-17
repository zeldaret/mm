.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Ending_Hero4_InitVars
/* 000116 0x80C23860 */ .word	0x02AA0400
/* 000117 0x80C23864 */ .word	0x00000009
/* 000118 0x80C23868 */ .word	0x01B60000
/* 000119 0x80C2386C */ .word	0x0000025C
/* 000120 0x80C23870 */ .word	EnEndingHero4_Init
/* 000121 0x80C23874 */ .word	EnEndingHero4_Destroy
/* 000122 0x80C23878 */ .word	EnEndingHero4_Update
/* 000123 0x80C2387C */ .word	EnEndingHero4_Draw
