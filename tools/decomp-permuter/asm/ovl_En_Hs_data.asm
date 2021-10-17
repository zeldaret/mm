.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Hs_InitVars
/* 000808 0x809538F0 */ .word	0x00A60400
/* 000809 0x809538F4 */ .word	0x00000019
/* 000810 0x809538F8 */ .word	0x00F50000
/* 000811 0x809538FC */ .word	0x00000398
/* 000812 0x80953900 */ .word	EnHs_Init
/* 000813 0x80953904 */ .word	EnHs_Destroy
/* 000814 0x80953908 */ .word	EnHs_Update
/* 000815 0x8095390C */ .word	EnHs_Draw
glabel D_80953910
/* 000816 0x80953910 */ .word	0x0A001139
/* 000817 0x80953914 */ .word	0x10010000
/* 000818 0x80953918 */ .word	0x00000000
/* 000819 0x8095391C */ .word	0x00000000
/* 000820 0x80953920 */ .word	0x00000000
/* 000821 0x80953924 */ .word	0xF7CFFFFF
/* 000822 0x80953928 */ .word	0x00000000
/* 000823 0x8095392C */ .word	0x00010100
/* 000824 0x80953930 */ .word	0x00280028
/* 000825 0x80953934 */ .word	0x00000000
/* 000826 0x80953938 */ .word	0x00000000
glabel D_8095393C
/* 000827 0x8095393C */ .word	0x43960000
/* 000828 0x80953940 */ .word	0x447A0000
/* 000829 0x80953944 */ .word	0x00000000
/* 000830 0x80953948 */ .word	0x00000000
/* 000831 0x8095394C */ .word	0x00000000
