.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel dmChar02OverlayInfo
/* 000380 0x80AAB420 */ .word	0x00000560
/* 000381 0x80AAB424 */ .word	0x00000080
/* 000382 0x80AAB428 */ .word	0x00000010
/* 000383 0x80AAB42C */ .word	0x00000000
/* 000384 0x80AAB430 */ .word	0x00000019
glabel dmChar02OverlayRelocations
/* 000385 0x80AAB434 */ .word	0x44000130
/* 000386 0x80AAB438 */ .word	0x45000178
/* 000387 0x80AAB43C */ .word	0x4600017C
/* 000388 0x80AAB440 */ .word	0x450001BC
/* 000389 0x80AAB444 */ .word	0x460001C0
/* 000390 0x80AAB448 */ .word	0x440001C8
/* 000391 0x80AAB44C */ .word	0x450001E0
/* 000392 0x80AAB450 */ .word	0x460001E4
/* 000393 0x80AAB454 */ .word	0x45000288
/* 000394 0x80AAB458 */ .word	0x460002C8
/* 000395 0x80AAB45C */ .word	0x440002EC
/* 000396 0x80AAB460 */ .word	0x45000328
/* 000397 0x80AAB464 */ .word	0x4600033C
/* 000398 0x80AAB468 */ .word	0x44000350
/* 000399 0x80AAB46C */ .word	0x440003F0
/* 000400 0x80AAB470 */ .word	0x45000518
/* 000401 0x80AAB474 */ .word	0x4600052C
/* 000402 0x80AAB478 */ .word	0x4500051C
/* 000403 0x80AAB47C */ .word	0x46000528
/* 000404 0x80AAB480 */ .word	0x45000520
/* 000405 0x80AAB484 */ .word	0x46000524
/* 000406 0x80AAB488 */ .word	0x82000010
/* 000407 0x80AAB48C */ .word	0x82000014
/* 000408 0x80AAB490 */ .word	0x82000018
/* 000409 0x80AAB494 */ .word	0x8200001C
/* 000410 0x80AAB498 */ .word	0x00000000
glabel dmChar02OverlayInfoOffset
/* 000411 0x80AAB49C */ .word	0x00000080
