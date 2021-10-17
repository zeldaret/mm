.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Box_InitVars
/* 002008 0x80869B30 */ .word	0x00060B00
/* 002009 0x80869B34 */ .word	0x00000000
/* 002010 0x80869B38 */ .word	0x000C0000
/* 002011 0x80869B3C */ .word	0x00000224
/* 002012 0x80869B40 */ .word	EnBox_Init
/* 002013 0x80869B44 */ .word	EnBox_Destroy
/* 002014 0x80869B48 */ .word	EnBox_Update
/* 002015 0x80869B4C */ .word	EnBox_Draw
glabel D_80869B50
/* 002016 0x80869B50 */ .word	0x001F0000
glabel D_80869B54
/* 002017 0x80869B54 */ .word	0x3FC00000
/* 002018 0x80869B58 */ .word	0x3F800000
/* 002019 0x80869B5C */ .word	0x3FC00000
/* 002020 0x80869B60 */ .word	0x3F800000
/* 002021 0x80869B64 */ .word	0x3FC00000
glabel D_80869B68
/* 002022 0x80869B68 */ .word	0x0600024C
/* 002023 0x80869B6C */ .word	0x06007E54
/* 002024 0x80869B70 */ .word	0x0600024C
/* 002025 0x80869B74 */ .word	0x06007F30
/* 002026 0x80869B78 */ .word	0x06000128
glabel D_80869B7C
/* 002027 0x80869B7C */ .word	0x00000000
/* 002028 0x80869B80 */ .word	0x3F800000
/* 002029 0x80869B84 */ .word	0x00000000
glabel D_80869B88
/* 002030 0x80869B88 */ .word	0x00000000
/* 002031 0x80869B8C */ .word	0x00000000
/* 002032 0x80869B90 */ .word	0x00000000
/* 002033 0x80869B94 */ .word	0x00000000
/* 002034 0x80869B98 */ .word	0x00000000
/* 002035 0x80869B9C */ .word	0x00000000
