.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Time_Tag_InitVars
/* 000716 0x80ACA9D0 */ .word	0x01AB0700
/* 000717 0x80ACA9D4 */ .word	0x00000010
/* 000718 0x80ACA9D8 */ .word	0x00010000
/* 000719 0x80ACA9DC */ .word	0x00000148
/* 000720 0x80ACA9E0 */ .word	EnTimeTag_Init
/* 000721 0x80ACA9E4 */ .word	EnTimeTag_Destroy
/* 000722 0x80ACA9E8 */ .word	EnTimeTag_Update
/* 000723 0x80ACA9EC */ .word	0x00000000
