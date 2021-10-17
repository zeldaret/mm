.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel dmTsgOverlayInfo
/* 000248 0x80A3B040 */ .word	0x000003B0
/* 000249 0x80A3B044 */ .word	0x00000020
/* 000250 0x80A3B048 */ .word	0x00000010
/* 000251 0x80A3B04C */ .word	0x00000000
/* 000252 0x80A3B050 */ .word	0x00000008
glabel dmTsgOverlayRelocations
/* 000253 0x80A3B054 */ .word	0x45000050
/* 000254 0x80A3B058 */ .word	0x46000054
/* 000255 0x80A3B05C */ .word	0x450002BC
/* 000256 0x80A3B060 */ .word	0x460002D0
/* 000257 0x80A3B064 */ .word	0x82000010
/* 000258 0x80A3B068 */ .word	0x82000014
/* 000259 0x80A3B06C */ .word	0x82000018
/* 000260 0x80A3B070 */ .word	0x8200001C
/* 000261 0x80A3B074 */ .word	0x00000000
/* 000262 0x80A3B078 */ .word	0x00000000
glabel dmTsgOverlayInfoOffset
/* 000263 0x80A3B07C */ .word	0x00000040
