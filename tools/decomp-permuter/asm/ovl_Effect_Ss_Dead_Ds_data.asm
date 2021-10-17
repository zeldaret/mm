.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80981700
/* 000264 0x80981700 */ .word	0x00000022
/* 000265 0x80981704 */ .word	func_809812E0
/* 000266 0x80981708 */ .word	0x00000000
/* 000267 0x8098170C */ .word	0x00000000
glabel D_80981710
/* 000268 0x80981710 */ .word	0x3C23D70A
glabel D_80981714
/* 000269 0x80981714 */ .word	0x3FC8F5C3
/* 000270 0x80981718 */ .word	0x00000000
/* 000271 0x8098171C */ .word	0x00000000
glabel effectSsDeadDsOverlayInfo
/* 000272 0x80981720 */ .word	0x00000420
/* 000273 0x80981724 */ .word	0x00000010
/* 000274 0x80981728 */ .word	0x00000010
/* 000275 0x8098172C */ .word	0x00000000
/* 000276 0x80981730 */ .word	0x00000009
glabel effectSsDeadDsOverlayRelocations
/* 000277 0x80981734 */ .word	0x45000040
/* 000278 0x80981738 */ .word	0x46000044
/* 000279 0x8098173C */ .word	0x45000058
/* 000280 0x80981740 */ .word	0x4600005C
/* 000281 0x80981744 */ .word	0x45000108
/* 000282 0x80981748 */ .word	0x4600010C
/* 000283 0x8098174C */ .word	0x45000314
/* 000284 0x80981750 */ .word	0x4600031C
/* 000285 0x80981754 */ .word	0x82000004
/* 000286 0x80981758 */ .word	0x00000000
glabel effectSsDeadDsOverlayInfoOffset
/* 000287 0x8098175C */ .word	0x00000040
