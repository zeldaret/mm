.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80979FF0
/* 000304 0x80979FF0 */ .word	0x00000009
/* 000305 0x80979FF4 */ .word	func_80979B30
/* 000306 0x80979FF8 */ .word	0x00000000
/* 000307 0x80979FFC */ .word	0x00000000
glabel D_8097A000
/* 000308 0x8097A000 */ .word	0x3B23D70A
/* 000309 0x8097A004 */ .word	0x00000000
/* 000310 0x8097A008 */ .word	0x00000000
/* 000311 0x8097A00C */ .word	0x00000000
glabel effectSsGRippleOverlayInfo
/* 000312 0x8097A010 */ .word	0x000004C0
/* 000313 0x8097A014 */ .word	0x00000010
/* 000314 0x8097A018 */ .word	0x00000010
/* 000315 0x8097A01C */ .word	0x00000000
/* 000316 0x8097A020 */ .word	0x00000008
glabel effectSsGRippleOverlayRelocations
/* 000317 0x8097A024 */ .word	0x45000060
/* 000318 0x8097A028 */ .word	0x46000068
/* 000319 0x8097A02C */ .word	0x45000064
/* 000320 0x8097A030 */ .word	0x4600006C
/* 000321 0x8097A034 */ .word	0x4500012C
/* 000322 0x8097A038 */ .word	0x46000130
/* 000323 0x8097A03C */ .word	0x44000338
/* 000324 0x8097A040 */ .word	0x82000004
/* 000325 0x8097A044 */ .word	0x00000000
/* 000326 0x8097A048 */ .word	0x00000000
glabel effectSsGRippleOverlayInfoOffset
/* 000327 0x8097A04C */ .word	0x00000040
