.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Attack_Niw_InitVars
/* 001040 0x80959100 */ .word	0x00AA0500
/* 001041 0x80959104 */ .word	0x00000010
/* 001042 0x80959108 */ .word	0x000F0000
/* 001043 0x8095910C */ .word	0x000002E0
/* 001044 0x80959110 */ .word	EnAttackNiw_Init
/* 001045 0x80959114 */ .word	EnAttackNiw_Destroy
/* 001046 0x80959118 */ .word	EnAttackNiw_Update
/* 001047 0x8095911C */ .word	EnAttackNiw_Draw
glabel D_80959120
/* 001048 0x80959120 */ .word	0x801F0001
/* 001049 0x80959124 */ .word	0xB874F830
/* 001050 0x80959128 */ .word	0x30540000
/* 001051 0x8095912C */ .word	0x00000000
