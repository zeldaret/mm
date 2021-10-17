.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enDemoheishiOverlayInfo
/* 000356 0x80BE9AA0 */ .word	0x00000520
/* 000357 0x80BE9AA4 */ .word	0x00000070
/* 000358 0x80BE9AA8 */ .word	0x00000000
/* 000359 0x80BE9AAC */ .word	0x00000000
/* 000360 0x80BE9AB0 */ .word	0x00000019
glabel enDemoheishiOverlayRelocations
/* 000361 0x80BE9AB4 */ .word	0x45000078
/* 000362 0x80BE9AB8 */ .word	0x46000084
/* 000363 0x80BE9ABC */ .word	0x44000094
/* 000364 0x80BE9AC0 */ .word	0x450000F0
/* 000365 0x80BE9AC4 */ .word	0x46000100
/* 000366 0x80BE9AC8 */ .word	0x45000124
/* 000367 0x80BE9ACC */ .word	0x46000138
/* 000368 0x80BE9AD0 */ .word	0x4500010C
/* 000369 0x80BE9AD4 */ .word	0x4600012C
/* 000370 0x80BE9AD8 */ .word	0x44000208
/* 000371 0x80BE9ADC */ .word	0x45000214
/* 000372 0x80BE9AE0 */ .word	0x46000230
/* 000373 0x80BE9AE4 */ .word	0x45000218
/* 000374 0x80BE9AE8 */ .word	0x46000224
/* 000375 0x80BE9AEC */ .word	0x440002AC
/* 000376 0x80BE9AF0 */ .word	0x450002E0
/* 000377 0x80BE9AF4 */ .word	0x460002E8
/* 000378 0x80BE9AF8 */ .word	0x4400033C
/* 000379 0x80BE9AFC */ .word	0x440003E0
/* 000380 0x80BE9B00 */ .word	0x450004DC
/* 000381 0x80BE9B04 */ .word	0x460004E0
/* 000382 0x80BE9B08 */ .word	0x82000010
/* 000383 0x80BE9B0C */ .word	0x82000014
/* 000384 0x80BE9B10 */ .word	0x82000018
/* 000385 0x80BE9B14 */ .word	0x8200001C
/* 000386 0x80BE9B18 */ .word	0x00000000
glabel enDemoheishiOverlayInfoOffset
/* 000387 0x80BE9B1C */ .word	0x00000080
