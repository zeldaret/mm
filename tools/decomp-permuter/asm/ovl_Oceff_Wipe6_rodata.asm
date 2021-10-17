.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel oceffWipe6OverlayInfo
/* 000372 0x80BCAB70 */ .word	0x00000310
/* 000373 0x80BCAB74 */ .word	0x000002B0
/* 000374 0x80BCAB78 */ .word	0x00000010
/* 000375 0x80BCAB7C */ .word	0x00000000
/* 000376 0x80BCAB80 */ .word	0x0000001A
glabel oceffWipe6OverlayRelocations
/* 000377 0x80BCAB84 */ .word	0x4500016C
/* 000378 0x80BCAB88 */ .word	0x46000170
/* 000379 0x80BCAB8C */ .word	0x45000188
/* 000380 0x80BCAB90 */ .word	0x4600018C
/* 000381 0x80BCAB94 */ .word	0x450001C4
/* 000382 0x80BCAB98 */ .word	0x460001C8
/* 000383 0x80BCAB9C */ .word	0x450001CC
/* 000384 0x80BCABA0 */ .word	0x460001D0
/* 000385 0x80BCABA4 */ .word	0x450001D4
/* 000386 0x80BCABA8 */ .word	0x460001E0
/* 000387 0x80BCABAC */ .word	0x4500019C
/* 000388 0x80BCABB0 */ .word	0x460001E4
/* 000389 0x80BCABB4 */ .word	0x450001D8
/* 000390 0x80BCABB8 */ .word	0x460001DC
/* 000391 0x80BCABBC */ .word	0x45000240
/* 000392 0x80BCABC0 */ .word	0x46000244
/* 000393 0x80BCABC4 */ .word	0x450002C4
/* 000394 0x80BCABC8 */ .word	0x460002D0
/* 000395 0x80BCABCC */ .word	0x450002D8
/* 000396 0x80BCABD0 */ .word	0x460002DC
/* 000397 0x80BCABD4 */ .word	0x82000010
/* 000398 0x80BCABD8 */ .word	0x82000014
/* 000399 0x80BCABDC */ .word	0x82000018
/* 000400 0x80BCABE0 */ .word	0x8200001C
/* 000401 0x80BCABE4 */ .word	0x8200002C
/* 000402 0x80BCABE8 */ .word	0x8200024C
glabel oceffWipe6OverlayInfoOffset
/* 000403 0x80BCABEC */ .word	0x00000080
