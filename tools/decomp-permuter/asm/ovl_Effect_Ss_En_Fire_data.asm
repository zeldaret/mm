.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80980570
/* 000388 0x80980570 */ .word	0x0000001D
/* 000389 0x80980574 */ .word	func_8097FF60
/* 000390 0x80980578 */ .word	0x00000000
/* 000391 0x8098057C */ .word	0x00000000
glabel D_80980580
/* 000392 0x80980580 */ .word	0x3851B717
glabel D_80980584
/* 000393 0x80980584 */ .word	0x414B3333
/* 000394 0x80980588 */ .word	0x00000000
/* 000395 0x8098058C */ .word	0x00000000
glabel effectSsEnFireOverlayInfo
/* 000396 0x80980590 */ .word	0x00000610
/* 000397 0x80980594 */ .word	0x00000010
/* 000398 0x80980598 */ .word	0x00000010
/* 000399 0x8098059C */ .word	0x00000000
/* 000400 0x809805A0 */ .word	0x00000009
glabel effectSsEnFireOverlayRelocations
/* 000401 0x809805A4 */ .word	0x45000078
/* 000402 0x809805A8 */ .word	0x46000084
/* 000403 0x809805AC */ .word	0x4500007C
/* 000404 0x809805B0 */ .word	0x46000088
/* 000405 0x809805B4 */ .word	0x450001F4
/* 000406 0x809805B8 */ .word	0x460001F8
/* 000407 0x809805BC */ .word	0x45000298
/* 000408 0x809805C0 */ .word	0x460002A0
/* 000409 0x809805C4 */ .word	0x82000004
/* 000410 0x809805C8 */ .word	0x00000000
glabel effectSsEnFireOverlayInfoOffset
/* 000411 0x809805CC */ .word	0x00000040
