.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_80ACB650
/* 000148 0x80ACB650 */ .word	0x3B03126F
/* 000149 0x80ACB654 */ .word	0x00000000
/* 000150 0x80ACB658 */ .word	0x00000000
/* 000151 0x80ACB65C */ .word	0x00000000
glabel bgFuKaitenOverlayInfo
/* 000152 0x80ACB660 */ .word	0x00000230
/* 000153 0x80ACB664 */ .word	0x00000020
/* 000154 0x80ACB668 */ .word	0x00000010
/* 000155 0x80ACB66C */ .word	0x00000000
/* 000156 0x80ACB670 */ .word	0x00000008
glabel bgFuKaitenOverlayRelocations
/* 000157 0x80ACB674 */ .word	0x450000D8
/* 000158 0x80ACB678 */ .word	0x460000DC
/* 000159 0x80ACB67C */ .word	0x44000180
/* 000160 0x80ACB680 */ .word	0x44000188
/* 000161 0x80ACB684 */ .word	0x82000010
/* 000162 0x80ACB688 */ .word	0x82000014
/* 000163 0x80ACB68C */ .word	0x82000018
/* 000164 0x80ACB690 */ .word	0x8200001C
/* 000165 0x80ACB694 */ .word	0x00000000
/* 000166 0x80ACB698 */ .word	0x00000000
glabel bgFuKaitenOverlayInfoOffset
/* 000167 0x80ACB69C */ .word	0x00000040
