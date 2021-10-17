.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Talk_InitVars
/* 000088 0x80BDE140 */ .word	0x02610700
/* 000089 0x80BDE144 */ .word	0x00000009
/* 000090 0x80BDE148 */ .word	0x00010000
/* 000091 0x80BDE14C */ .word	0x00000148
/* 000092 0x80BDE150 */ .word	EnTalk_Init
/* 000093 0x80BDE154 */ .word	EnTalk_Destroy
/* 000094 0x80BDE158 */ .word	EnTalk_Update
/* 000095 0x80BDE15C */ .word	0x00000000
