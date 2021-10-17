.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Tanron6_InitVars
/* 000068 0x80BE6150 */ .word	0x02690500
/* 000069 0x80BE6154 */ .word	0x00000005
/* 000070 0x80BE6158 */ .word	0x02400000
/* 000071 0x80BE615C */ .word	0x00000204
/* 000072 0x80BE6160 */ .word	EnTanron6_Init
/* 000073 0x80BE6164 */ .word	EnTanron6_Destroy
/* 000074 0x80BE6168 */ .word	EnTanron6_Update
/* 000075 0x80BE616C */ .word	EnTanron6_Draw
glabel D_80BE6170
/* 000076 0x80BE6170 */ .word	0xF0F000F1
/* 000077 0x80BE6174 */ .word	0xE1E100E1
/* 000078 0x80BE6178 */ .word	0xF0F0F0E1
/* 000079 0x80BE617C */ .word	0xE146F0F0
/* 000080 0x80BE6180 */ .word	0xE1F0F000
/* 000081 0x80BE6184 */ .word	0x00F0E100
/* 000082 0x80BE6188 */ .word	0xF0000000
/* 000083 0x80BE618C */ .word	0x000000F0
