.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enDrsOverlayInfo
/* 000232 0x80C1E630 */ .word	0x00000330
/* 000233 0x80C1E634 */ .word	0x00000070
/* 000234 0x80C1E638 */ .word	0x00000000
/* 000235 0x80C1E63C */ .word	0x00000000
/* 000236 0x80C1E640 */ .word	0x00000012
glabel enDrsOverlayRelocations
/* 000237 0x80C1E644 */ .word	0x450000C8
/* 000238 0x80C1E648 */ .word	0x460000CC
/* 000239 0x80C1E64C */ .word	0x450000DC
/* 000240 0x80C1E650 */ .word	0x460000E0
/* 000241 0x80C1E654 */ .word	0x450000FC
/* 000242 0x80C1E658 */ .word	0x46000100
/* 000243 0x80C1E65C */ .word	0x45000120
/* 000244 0x80C1E660 */ .word	0x46000128
/* 000245 0x80C1E664 */ .word	0x45000124
/* 000246 0x80C1E668 */ .word	0x4600012C
/* 000247 0x80C1E66C */ .word	0x45000174
/* 000248 0x80C1E670 */ .word	0x46000178
/* 000249 0x80C1E674 */ .word	0x44000208
/* 000250 0x80C1E678 */ .word	0x450002F8
/* 000251 0x80C1E67C */ .word	0x460002FC
/* 000252 0x80C1E680 */ .word	0x82000010
/* 000253 0x80C1E684 */ .word	0x82000014
/* 000254 0x80C1E688 */ .word	0x82000018
glabel enDrsOverlayInfoOffset
/* 000255 0x80C1E68C */ .word	0x00000060
