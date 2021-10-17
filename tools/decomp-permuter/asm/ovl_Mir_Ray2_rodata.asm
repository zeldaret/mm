.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_80AF4390
/* 000264 0x80AF4390 */ .word	0x3CA3D70A
/* 000265 0x80AF4394 */ .word	0x00000000
/* 000266 0x80AF4398 */ .word	0x00000000
/* 000267 0x80AF439C */ .word	0x00000000
glabel mirRay2OverlayInfo
/* 000268 0x80AF43A0 */ .word	0x000003C0
/* 000269 0x80AF43A4 */ .word	0x00000060
/* 000270 0x80AF43A8 */ .word	0x00000010
/* 000271 0x80AF43AC */ .word	0x00000000
/* 000272 0x80AF43B0 */ .word	0x0000000D
glabel mirRay2OverlayRelocations
/* 000273 0x80AF43B4 */ .word	0x450001AC
/* 000274 0x80AF43B8 */ .word	0x460001B0
/* 000275 0x80AF43BC */ .word	0x440001DC
/* 000276 0x80AF43C0 */ .word	0x45000208
/* 000277 0x80AF43C4 */ .word	0x46000218
/* 000278 0x80AF43C8 */ .word	0x44000228
/* 000279 0x80AF43CC */ .word	0x44000330
/* 000280 0x80AF43D0 */ .word	0x4400037C
/* 000281 0x80AF43D4 */ .word	0x82000010
/* 000282 0x80AF43D8 */ .word	0x82000014
/* 000283 0x80AF43DC */ .word	0x82000018
/* 000284 0x80AF43E0 */ .word	0x8200001C
/* 000285 0x80AF43E4 */ .word	0x82000050
/* 000286 0x80AF43E8 */ .word	0x00000000
glabel mirRay2OverlayInfoOffset
/* 000287 0x80AF43EC */ .word	0x00000050
