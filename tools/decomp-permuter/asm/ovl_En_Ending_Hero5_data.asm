.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Ending_Hero5_InitVars
/* 000196 0x80C23BD0 */ .word	0x02AB0400
/* 000197 0x80C23BD4 */ .word	0x00000009
/* 000198 0x80C23BD8 */ .word	0x00F10000
/* 000199 0x80C23BDC */ .word	0x00000260
/* 000200 0x80C23BE0 */ .word	EnEndingHero5_Init
/* 000201 0x80C23BE4 */ .word	EnEndingHero5_Destroy
/* 000202 0x80C23BE8 */ .word	EnEndingHero5_Update
/* 000203 0x80C23BEC */ .word	EnEndingHero5_Draw
glabel D_80C23BF0
/* 000204 0x80C23BF0 */ .word	0x060070C0
/* 000205 0x80C23BF4 */ .word	0x06006FB0
/* 000206 0x80C23BF8 */ .word	0x06006E80
/* 000207 0x80C23BFC */ .word	0x06006D70
/* 000208 0x80C23C00 */ .word	0x0600A390
/* 000209 0x80C23C04 */ .word	0x00000000
/* 000210 0x80C23C08 */ .word	0x00000000
/* 000211 0x80C23C0C */ .word	0x00000000
