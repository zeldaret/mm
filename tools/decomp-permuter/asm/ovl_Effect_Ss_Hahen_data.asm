.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_8097B790
/* 000328 0x8097B790 */ .word	0x0000000F
/* 000329 0x8097B794 */ .word	func_8097B2E4
/* 000330 0x8097B798 */ .word	0x00000000
/* 000331 0x8097B79C */ .word	0x00000000
glabel D_8097B7A0
/* 000332 0x8097B7A0 */ .word	0x38D1B718
glabel D_8097B7A4
/* 000333 0x8097B7A4 */ .word	0x3A83126F
glabel D_8097B7A8
/* 000334 0x8097B7A8 */ .word	0x3C23D70A
glabel D_8097B7AC
/* 000335 0x8097B7AC */ .word	0x3C23D70A
glabel effectSsHahenOverlayInfo
/* 000336 0x8097B7B0 */ .word	0x00000520
/* 000337 0x8097B7B4 */ .word	0x00000010
/* 000338 0x8097B7B8 */ .word	0x00000010
/* 000339 0x8097B7BC */ .word	0x00000000
/* 000340 0x8097B7C0 */ .word	0x00000011
glabel effectSsHahenOverlayRelocations
/* 000341 0x8097B7C4 */ .word	0x4400010C
/* 000342 0x8097B7C8 */ .word	0x45000124
/* 000343 0x8097B7CC */ .word	0x4600012C
/* 000344 0x8097B7D0 */ .word	0x45000128
/* 000345 0x8097B7D4 */ .word	0x46000130
/* 000346 0x8097B7D8 */ .word	0x450003A8
/* 000347 0x8097B7DC */ .word	0x460003AC
/* 000348 0x8097B7E0 */ .word	0x450003CC
/* 000349 0x8097B7E4 */ .word	0x460003D0
/* 000350 0x8097B7E8 */ .word	0x450003FC
/* 000351 0x8097B7EC */ .word	0x46000400
/* 000352 0x8097B7F0 */ .word	0x45000420
/* 000353 0x8097B7F4 */ .word	0x46000424
/* 000354 0x8097B7F8 */ .word	0x4400046C
/* 000355 0x8097B7FC */ .word	0x4400047C
/* 000356 0x8097B800 */ .word	0x44000508
/* 000357 0x8097B804 */ .word	0x82000004
/* 000358 0x8097B808 */ .word	0x00000000
glabel effectSsHahenOverlayInfoOffset
/* 000359 0x8097B80C */ .word	0x00000060
