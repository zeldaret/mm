.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objMilkBinOverlayInfo
/* 000148 0x80C09090 */ .word	0x000001F0
/* 000149 0x80C09094 */ .word	0x00000050
/* 000150 0x80C09098 */ .word	0x00000010
/* 000151 0x80C0909C */ .word	0x00000000
/* 000152 0x80C090A0 */ .word	0x00000008
glabel objMilkBinOverlayRelocations
/* 000153 0x80C090A4 */ .word	0x45000014
/* 000154 0x80C090A8 */ .word	0x46000018
/* 000155 0x80C090AC */ .word	0x4500003C
/* 000156 0x80C090B0 */ .word	0x46000040
/* 000157 0x80C090B4 */ .word	0x82000010
/* 000158 0x80C090B8 */ .word	0x82000014
/* 000159 0x80C090BC */ .word	0x82000018
/* 000160 0x80C090C0 */ .word	0x8200001C
/* 000161 0x80C090C4 */ .word	0x00000000
/* 000162 0x80C090C8 */ .word	0x00000000
glabel objMilkBinOverlayInfoOffset
/* 000163 0x80C090CC */ .word	0x00000040
