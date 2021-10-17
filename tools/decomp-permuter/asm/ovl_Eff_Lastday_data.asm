.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Eff_Lastday_InitVars
/* 000436 0x80BEC190 */ .word	0x02720700
/* 000437 0x80BEC194 */ .word	0x00000030
/* 000438 0x80BEC198 */ .word	0x02460000
/* 000439 0x80BEC19C */ .word	0x00000158
/* 000440 0x80BEC1A0 */ .word	EffLastday_Init
/* 000441 0x80BEC1A4 */ .word	EffLastday_Destroy
/* 000442 0x80BEC1A8 */ .word	EffLastday_Update
/* 000443 0x80BEC1AC */ .word	EffLastday_Draw
