.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Botihasira_InitVars
/* 000148 0x80B282D0 */ .word	0x01F00700
/* 000149 0x80B282D4 */ .word	0x00000000
/* 000150 0x80B282D8 */ .word	0x01C90000
/* 000151 0x80B282DC */ .word	0x000001AC
/* 000152 0x80B282E0 */ .word	BgBotihasira_Init
/* 000153 0x80B282E4 */ .word	BgBotihasira_Destroy
/* 000154 0x80B282E8 */ .word	BgBotihasira_Update
/* 000155 0x80B282EC */ .word	BgBotihasira_Draw
glabel D_80B282F0
/* 000156 0x80B282F0 */ .word	0x09000939
/* 000157 0x80B282F4 */ .word	0x10010000
/* 000158 0x80B282F8 */ .word	0x02000000
/* 000159 0x80B282FC */ .word	0xF7CFFFFF
/* 000160 0x80B28300 */ .word	0x00000000
/* 000161 0x80B28304 */ .word	0xF7CFFFFF
/* 000162 0x80B28308 */ .word	0x00000000
/* 000163 0x80B2830C */ .word	0x00010100
/* 000164 0x80B28310 */ .word	0x001B0050
/* 000165 0x80B28314 */ .word	0x00000000
/* 000166 0x80B28318 */ .word	0x00000000
/* 000167 0x80B2831C */ .word	0x00000000
