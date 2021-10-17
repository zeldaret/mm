.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Bh_InitVars
/* 000288 0x80C231C0 */ .word	0x02A70700
/* 000289 0x80C231C4 */ .word	0x00000000
/* 000290 0x80C231C8 */ .word	0x027A0000
/* 000291 0x80C231CC */ .word	0x000001EC
/* 000292 0x80C231D0 */ .word	EnBh_Init
/* 000293 0x80C231D4 */ .word	EnBh_Destroy
/* 000294 0x80C231D8 */ .word	EnBh_Update
/* 000295 0x80C231DC */ .word	EnBh_Draw
