.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80981270
/* 000328 0x80981270 */ .word	0x00000021
/* 000329 0x80981274 */ .word	func_80980D50
/* 000330 0x80981278 */ .word	0x00000000
/* 000331 0x8098127C */ .word	0x00000000
glabel D_80981280
/* 000332 0x80981280 */ .word	0x3C23D70A
/* 000333 0x80981284 */ .word	0x00000000
/* 000334 0x80981288 */ .word	0x00000000
/* 000335 0x8098128C */ .word	0x00000000
glabel effectSsDeadDdOverlayInfo
/* 000336 0x80981290 */ .word	0x00000520
/* 000337 0x80981294 */ .word	0x00000010
/* 000338 0x80981298 */ .word	0x00000010
/* 000339 0x8098129C */ .word	0x00000000
/* 000340 0x809812A0 */ .word	0x0000000B
glabel effectSsDeadDdOverlayRelocations
/* 000341 0x809812A4 */ .word	0x45000068
/* 000342 0x809812A8 */ .word	0x4600006C
/* 000343 0x809812AC */ .word	0x45000078
/* 000344 0x809812B0 */ .word	0x4600007C
/* 000345 0x809812B4 */ .word	0x45000158
/* 000346 0x809812B8 */ .word	0x4600017C
/* 000347 0x809812BC */ .word	0x4500015C
/* 000348 0x809812C0 */ .word	0x46000190
/* 000349 0x809812C4 */ .word	0x450002F0
/* 000350 0x809812C8 */ .word	0x460002F4
/* 000351 0x809812CC */ .word	0x82000004
/* 000352 0x809812D0 */ .word	0x00000000
/* 000353 0x809812D4 */ .word	0x00000000
/* 000354 0x809812D8 */ .word	0x00000000
glabel effectSsDeadDdOverlayInfoOffset
/* 000355 0x809812DC */ .word	0x00000050
