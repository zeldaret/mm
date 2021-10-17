.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enPartOverlayInfo
/* 000368 0x80865930 */ .word	0x00000570
/* 000369 0x80865934 */ .word	0x00000040
/* 000370 0x80865938 */ .word	0x00000010
/* 000371 0x8086593C */ .word	0x00000000
/* 000372 0x80865940 */ .word	0x00000010
glabel enPartOverlayRelocations
/* 000373 0x80865944 */ .word	0x45000040
/* 000374 0x80865948 */ .word	0x46000044
/* 000375 0x8086594C */ .word	0x450000D4
/* 000376 0x80865950 */ .word	0x460000D8
/* 000377 0x80865954 */ .word	0x450000E4
/* 000378 0x80865958 */ .word	0x460000F4
/* 000379 0x8086595C */ .word	0x4500018C
/* 000380 0x80865960 */ .word	0x46000190
/* 000381 0x80865964 */ .word	0x45000448
/* 000382 0x80865968 */ .word	0x4600045C
/* 000383 0x8086596C */ .word	0x82000010
/* 000384 0x80865970 */ .word	0x82000014
/* 000385 0x80865974 */ .word	0x82000018
/* 000386 0x80865978 */ .word	0x8200001C
/* 000387 0x8086597C */ .word	0x8200002C
/* 000388 0x80865980 */ .word	0x82000030
/* 000389 0x80865984 */ .word	0x00000000
/* 000390 0x80865988 */ .word	0x00000000
glabel enPartOverlayInfoOffset
/* 000391 0x8086598C */ .word	0x00000060
