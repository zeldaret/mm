.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_80ACE2B0
/* 000376 0x80ACE2B0 */ .word	0x3DA3D70A
glabel D_80ACE2B4
/* 000377 0x80ACE2B4 */ .word	0x3DCCCCCD
/* 000378 0x80ACE2B8 */ .word	0x00000000
/* 000379 0x80ACE2BC */ .word	0x00000000
glabel enElfbubOverlayInfo
/* 000380 0x80ACE2C0 */ .word	0x00000580
/* 000381 0x80ACE2C4 */ .word	0x00000060
/* 000382 0x80ACE2C8 */ .word	0x00000010
/* 000383 0x80ACE2CC */ .word	0x00000000
/* 000384 0x80ACE2D0 */ .word	0x00000014
glabel enElfbubOverlayRelocations
/* 000385 0x80ACE2D4 */ .word	0x4500006C
/* 000386 0x80ACE2D8 */ .word	0x46000074
/* 000387 0x80ACE2DC */ .word	0x45000090
/* 000388 0x80ACE2E0 */ .word	0x460000A4
/* 000389 0x80ACE2E4 */ .word	0x45000098
/* 000390 0x80ACE2E8 */ .word	0x4600009C
/* 000391 0x80ACE2EC */ .word	0x45000198
/* 000392 0x80ACE2F0 */ .word	0x4600019C
/* 000393 0x80ACE2F4 */ .word	0x45000264
/* 000394 0x80ACE2F8 */ .word	0x46000284
/* 000395 0x80ACE2FC */ .word	0x45000270
/* 000396 0x80ACE300 */ .word	0x46000280
/* 000397 0x80ACE304 */ .word	0x45000274
/* 000398 0x80ACE308 */ .word	0x4600027C
/* 000399 0x80ACE30C */ .word	0x45000390
/* 000400 0x80ACE310 */ .word	0x46000394
/* 000401 0x80ACE314 */ .word	0x82000010
/* 000402 0x80ACE318 */ .word	0x82000014
/* 000403 0x80ACE31C */ .word	0x82000018
/* 000404 0x80ACE320 */ .word	0x8200001C
/* 000405 0x80ACE324 */ .word	0x00000000
/* 000406 0x80ACE328 */ .word	0x00000000
glabel enElfbubOverlayInfoOffset
/* 000407 0x80ACE32C */ .word	0x00000070
