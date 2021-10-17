.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_8097FED0
/* 000404 0x8097FED0 */ .word	0x0000001C
/* 000405 0x8097FED4 */ .word	func_8097F880
/* 000406 0x8097FED8 */ .word	0x00000000
/* 000407 0x8097FEDC */ .word	0x00000000
glabel D_8097FEE0
/* 000408 0x8097FEE0 */ .word	0x3DCCCCCD
glabel D_8097FEE4
/* 000409 0x8097FEE4 */ .word	0x3C8EFA35
glabel D_8097FEE8
/* 000410 0x8097FEE8 */ .word	0x3727C5AD
glabel D_8097FEEC
/* 000411 0x8097FEEC */ .word	0x3DCCCCCD
glabel D_8097FEF0
/* 000412 0x8097FEF0 */ .word	0x3C23D70A
glabel D_8097FEF4
/* 000413 0x8097FEF4 */ .word	0x3F666666
/* 000414 0x8097FEF8 */ .word	0x00000000
/* 000415 0x8097FEFC */ .word	0x00000000
glabel effectSsFireTailOverlayInfo
/* 000416 0x8097FF00 */ .word	0x00000650
/* 000417 0x8097FF04 */ .word	0x00000010
/* 000418 0x8097FF08 */ .word	0x00000020
/* 000419 0x8097FF0C */ .word	0x00000000
/* 000420 0x8097FF10 */ .word	0x00000011
glabel effectSsFireTailOverlayRelocations
/* 000421 0x8097FF14 */ .word	0x45000010
/* 000422 0x8097FF18 */ .word	0x46000020
/* 000423 0x8097FF1C */ .word	0x45000014
/* 000424 0x8097FF20 */ .word	0x46000024
/* 000425 0x8097FF24 */ .word	0x450002FC
/* 000426 0x8097FF28 */ .word	0x46000300
/* 000427 0x8097FF2C */ .word	0x45000358
/* 000428 0x8097FF30 */ .word	0x4600035C
/* 000429 0x8097FF34 */ .word	0x450003AC
/* 000430 0x8097FF38 */ .word	0x460003C0
/* 000431 0x8097FF3C */ .word	0x450003F8
/* 000432 0x8097FF40 */ .word	0x460003FC
/* 000433 0x8097FF44 */ .word	0x45000410
/* 000434 0x8097FF48 */ .word	0x46000414
/* 000435 0x8097FF4C */ .word	0x45000618
/* 000436 0x8097FF50 */ .word	0x4600061C
/* 000437 0x8097FF54 */ .word	0x82000004
/* 000438 0x8097FF58 */ .word	0x00000000
glabel effectSsFireTailOverlayInfoOffset
/* 000439 0x8097FF5C */ .word	0x00000060
