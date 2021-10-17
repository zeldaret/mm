.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objTokeiTobiraOverlayInfo
/* 000372 0x80ABD7A0 */ .word	0x00000560
/* 000373 0x80ABD7A4 */ .word	0x00000060
/* 000374 0x80ABD7A8 */ .word	0x00000010
/* 000375 0x80ABD7AC */ .word	0x00000000
/* 000376 0x80ABD7B0 */ .word	0x0000001E
glabel objTokeiTobiraOverlayRelocations
/* 000377 0x80ABD7B4 */ .word	0x45000018
/* 000378 0x80ABD7B8 */ .word	0x4600001C
/* 000379 0x80ABD7BC */ .word	0x45000040
/* 000380 0x80ABD7C0 */ .word	0x46000050
/* 000381 0x80ABD7C4 */ .word	0x450000B8
/* 000382 0x80ABD7C8 */ .word	0x460000BC
/* 000383 0x80ABD7CC */ .word	0x450000E8
/* 000384 0x80ABD7D0 */ .word	0x460000EC
/* 000385 0x80ABD7D4 */ .word	0x45000104
/* 000386 0x80ABD7D8 */ .word	0x46000110
/* 000387 0x80ABD7DC */ .word	0x45000178
/* 000388 0x80ABD7E0 */ .word	0x46000188
/* 000389 0x80ABD7E4 */ .word	0x4500026C
/* 000390 0x80ABD7E8 */ .word	0x4600027C
/* 000391 0x80ABD7EC */ .word	0x4500031C
/* 000392 0x80ABD7F0 */ .word	0x46000320
/* 000393 0x80ABD7F4 */ .word	0x4500037C
/* 000394 0x80ABD7F8 */ .word	0x46000380
/* 000395 0x80ABD7FC */ .word	0x45000444
/* 000396 0x80ABD800 */ .word	0x46000454
/* 000397 0x80ABD804 */ .word	0x45000490
/* 000398 0x80ABD808 */ .word	0x46000494
/* 000399 0x80ABD80C */ .word	0x450004B8
/* 000400 0x80ABD810 */ .word	0x460004CC
/* 000401 0x80ABD814 */ .word	0x45000534
/* 000402 0x80ABD818 */ .word	0x4600054C
/* 000403 0x80ABD81C */ .word	0x82000010
/* 000404 0x80ABD820 */ .word	0x82000014
/* 000405 0x80ABD824 */ .word	0x82000018
/* 000406 0x80ABD828 */ .word	0x8200001C
glabel objTokeiTobiraOverlayInfoOffset
/* 000407 0x80ABD82C */ .word	0x00000090
