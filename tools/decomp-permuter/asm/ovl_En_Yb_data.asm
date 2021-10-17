.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Yb_InitVars
/* 001124 0x80BFB290 */ .word	0x027A0400
/* 001125 0x80BFB294 */ .word	0x02000019
/* 001126 0x80BFB298 */ .word	0x024A0000
/* 001127 0x80BFB29C */ .word	0x00000424
/* 001128 0x80BFB2A0 */ .word	EnYb_Init
/* 001129 0x80BFB2A4 */ .word	EnYb_Destroy
/* 001130 0x80BFB2A8 */ .word	EnYb_Update
/* 001131 0x80BFB2AC */ .word	EnYb_Draw
glabel D_80BFB2B0
/* 001132 0x80BFB2B0 */ .word	0x0A001139
/* 001133 0x80BFB2B4 */ .word	0x10010000
/* 001134 0x80BFB2B8 */ .word	0x00000000
/* 001135 0x80BFB2BC */ .word	0x00000000
/* 001136 0x80BFB2C0 */ .word	0x00000000
/* 001137 0x80BFB2C4 */ .word	0xF7CFFFFF
/* 001138 0x80BFB2C8 */ .word	0x00000000
/* 001139 0x80BFB2CC */ .word	0x00010100
/* 001140 0x80BFB2D0 */ .word	0x00140028
/* 001141 0x80BFB2D4 */ .word	0x00000000
/* 001142 0x80BFB2D8 */ .word	0x00000000
glabel D_80BFB2DC
/* 001143 0x80BFB2DC */ .word	0x06000200
glabel D_80BFB2E0
/* 001144 0x80BFB2E0 */ .word	0x0400DF28
/* 001145 0x80BFB2E4 */ .word	0x0400CF98
glabel D_80BFB2E8
/* 001146 0x80BFB2E8 */ .word	0x00000000
/* 001147 0x80BFB2EC */ .word	0x3F000000
/* 001148 0x80BFB2F0 */ .word	0x00000000
glabel D_80BFB2F4
/* 001149 0x80BFB2F4 */ .word	0x43FA0000
/* 001150 0x80BFB2F8 */ .word	0xC3FA0000
/* 001151 0x80BFB2FC */ .word	0x00000000
glabel D_80BFB300
/* 001152 0x80BFB300 */ .word	0x43FA0000
/* 001153 0x80BFB304 */ .word	0xC3FA0000
/* 001154 0x80BFB308 */ .word	0x00000000
/* 001155 0x80BFB30C */ .word	0x00000000
