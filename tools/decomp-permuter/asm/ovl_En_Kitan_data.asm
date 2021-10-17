.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Kitan_InitVars
/* 000792 0x80C09D30 */ .word	0x028C0400
/* 000793 0x80C09D34 */ .word	0x00000009
/* 000794 0x80C09D38 */ .word	0x02640000
/* 000795 0x80C09D3C */ .word	0x000002DC
/* 000796 0x80C09D40 */ .word	EnKitan_Init
/* 000797 0x80C09D44 */ .word	EnKitan_Destroy
/* 000798 0x80C09D48 */ .word	EnKitan_Update
/* 000799 0x80C09D4C */ .word	0x00000000
glabel D_80C09D50
/* 000800 0x80C09D50 */ .word	0x0A001139
/* 000801 0x80C09D54 */ .word	0x10010000
/* 000802 0x80C09D58 */ .word	0x00000000
/* 000803 0x80C09D5C */ .word	0x00000000
/* 000804 0x80C09D60 */ .word	0x00000000
/* 000805 0x80C09D64 */ .word	0xF7CFFFFF
/* 000806 0x80C09D68 */ .word	0x00000000
/* 000807 0x80C09D6C */ .word	0x00010100
/* 000808 0x80C09D70 */ .word	0x00140028
/* 000809 0x80C09D74 */ .word	0x00000000
/* 000810 0x80C09D78 */ .word	0x00000000
glabel D_80C09D7C
/* 000811 0x80C09D7C */ .word	0xFFFFFFFF
glabel D_80C09D80
/* 000812 0x80C09D80 */ .word	0xFFFFC8FF
glabel D_80C09D84
/* 000813 0x80C09D84 */ .word	0x00000000
/* 000814 0x80C09D88 */ .word	0x00000000
/* 000815 0x80C09D8C */ .word	0x00000000
