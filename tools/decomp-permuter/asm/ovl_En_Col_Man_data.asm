.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80AFE730
/* 000700 0x80AFE730 */ .word	0x0A000001
/* 000701 0x80AFE734 */ .word	0x10010000
/* 000702 0x80AFE738 */ .word	0x00000000
/* 000703 0x80AFE73C */ .word	0xF7CFFFFF
/* 000704 0x80AFE740 */ .word	0x00000000
/* 000705 0x80AFE744 */ .word	0xF7CFFFFF
/* 000706 0x80AFE748 */ .word	0x00000000
/* 000707 0x80AFE74C */ .word	0x00000100
/* 000708 0x80AFE750 */ .word	0x000A000B
/* 000709 0x80AFE754 */ .word	0x00010000
/* 000710 0x80AFE758 */ .word	0x00000000
glabel En_Col_Man_InitVars
/* 000711 0x80AFE75C */ .word	0x01D90800
/* 000712 0x80AFE760 */ .word	0x00100000
/* 000713 0x80AFE764 */ .word	0x00010000
/* 000714 0x80AFE768 */ .word	0x000001A0
/* 000715 0x80AFE76C */ .word	EnColMan_Init
/* 000716 0x80AFE770 */ .word	EnColMan_Destroy
/* 000717 0x80AFE774 */ .word	EnColMan_Update
/* 000718 0x80AFE778 */ .word	0x00000000
glabel D_80AFE77C
/* 000719 0x80AFE77C */ .word	0x3C3214FF
glabel D_80AFE780
/* 000720 0x80AFE780 */ .word	0x281E1EFF
/* 000721 0x80AFE784 */ .word	0x00000000
/* 000722 0x80AFE788 */ .word	0x00000000
/* 000723 0x80AFE78C */ .word	0x00000000
