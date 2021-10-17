.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Eff_Dust_InitVars
/* 001172 0x80919D90 */ .word	0x007B0400
/* 001173 0x80919D94 */ .word	0x00000030
/* 001174 0x80919D98 */ .word	0x00010000
/* 001175 0x80919D9C */ .word	0x00000560
/* 001176 0x80919DA0 */ .word	EffDust_Init
/* 001177 0x80919DA4 */ .word	EffDust_Destroy
/* 001178 0x80919DA8 */ .word	EffDust_Update
/* 001179 0x80919DAC */ .word	EffDust_Draw
glabel D_80919DB0
/* 001180 0x80919DB0 */ .word	0xDF000000
/* 001181 0x80919DB4 */ .word	0x00000000
/* 001182 0x80919DB8 */ .word	0x00000000
/* 001183 0x80919DBC */ .word	0x00000000
