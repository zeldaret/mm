.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Weather_Tag_InitVars
/* 001252 0x809677A0 */ .word	0x00BC0600
/* 001253 0x809677A4 */ .word	0x00000010
/* 001254 0x809677A8 */ .word	0x00010000
/* 001255 0x809677AC */ .word	0x0000015C
/* 001256 0x809677B0 */ .word	EnWeatherTag_Init
/* 001257 0x809677B4 */ .word	EnWeatherTag_Destroy
/* 001258 0x809677B8 */ .word	EnWeatherTag_Update
/* 001259 0x809677BC */ .word	EnWeatherTag_Draw
