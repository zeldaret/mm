.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80979560
/* 000236 0x80979560 */ .word	0x00000006
/* 000237 0x80979564 */ .word	func_80979228
glabel D_80979568
/* 000238 0x80979568 */ .word	0x060090A0
/* 000239 0x8097956C */ .word	0x060092A0
/* 000240 0x80979570 */ .word	0x060094A0
/* 000241 0x80979574 */ .word	0x060096A0
/* 000242 0x80979578 */ .word	0x00000000
/* 000243 0x8097957C */ .word	0x00000000
glabel effectSsDFireOverlayInfo
/* 000244 0x80979580 */ .word	0x000003B0
/* 000245 0x80979584 */ .word	0x00000020
/* 000246 0x80979588 */ .word	0x00000000
/* 000247 0x8097958C */ .word	0x00000000
/* 000248 0x80979590 */ .word	0x0000000A
glabel effectSsDFireOverlayRelocations
/* 000249 0x80979594 */ .word	0x4400009C
/* 000250 0x80979598 */ .word	0x450000DC
/* 000251 0x8097959C */ .word	0x460000EC
/* 000252 0x809795A0 */ .word	0x450000E0
/* 000253 0x809795A4 */ .word	0x460000F0
/* 000254 0x809795A8 */ .word	0x44000184
/* 000255 0x809795AC */ .word	0x450002BC
/* 000256 0x809795B0 */ .word	0x460002C8
/* 000257 0x809795B4 */ .word	0x44000398
/* 000258 0x809795B8 */ .word	0x82000004
glabel effectSsDFireOverlayInfoOffset
/* 000259 0x809795BC */ .word	0x00000040
