.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_809808E0
/* 000196 0x809808E0 */ .word	0x001E003C
/* 000197 0x809808E4 */ .word	0x00640000
glabel D_809808E8
/* 000198 0x809808E8 */ .word	0x0000001E
/* 000199 0x809808EC */ .word	func_809805D0
glabel D_809808F0
/* 000200 0x809808F0 */ .word	0x06000000
/* 000201 0x809808F4 */ .word	0x06000480
/* 000202 0x809808F8 */ .word	0x06000900
/* 000203 0x809808FC */ .word	0x00000000
glabel effectSsExtraOverlayInfo
/* 000204 0x80980900 */ .word	0x00000310
/* 000205 0x80980904 */ .word	0x00000020
/* 000206 0x80980908 */ .word	0x00000000
/* 000207 0x8098090C */ .word	0x00000000
/* 000208 0x80980910 */ .word	0x00000009
glabel effectSsExtraOverlayRelocations
/* 000209 0x80980914 */ .word	0x450000A4
/* 000210 0x80980918 */ .word	0x460000B4
/* 000211 0x8098091C */ .word	0x450000A8
/* 000212 0x80980920 */ .word	0x460000B8
/* 000213 0x80980924 */ .word	0x45000258
/* 000214 0x80980928 */ .word	0x4600026C
/* 000215 0x8098092C */ .word	0x450002E4
/* 000216 0x80980930 */ .word	0x460002F4
/* 000217 0x80980934 */ .word	0x8200000C
/* 000218 0x80980938 */ .word	0x00000000
glabel effectSsExtraOverlayInfoOffset
/* 000219 0x8098093C */ .word	0x00000040
