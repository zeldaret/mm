.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgCtowerGearOverlayInfo
/* 000484 0x80AD3300 */ .word	0x000006E0
/* 000485 0x80AD3304 */ .word	0x000000B0
/* 000486 0x80AD3308 */ .word	0x00000000
/* 000487 0x80AD330C */ .word	0x00000000
/* 000488 0x80AD3310 */ .word	0x00000017
glabel bgCtowerGearOverlayRelocations
/* 000489 0x80AD3314 */ .word	0x450000D4
/* 000490 0x80AD3318 */ .word	0x460000D8
/* 000491 0x80AD331C */ .word	0x450001F0
/* 000492 0x80AD3320 */ .word	0x460001FC
/* 000493 0x80AD3324 */ .word	0x450001F4
/* 000494 0x80AD3328 */ .word	0x460001F8
/* 000495 0x80AD332C */ .word	0x45000350
/* 000496 0x80AD3330 */ .word	0x46000358
/* 000497 0x80AD3334 */ .word	0x45000370
/* 000498 0x80AD3338 */ .word	0x46000374
/* 000499 0x80AD333C */ .word	0x45000380
/* 000500 0x80AD3340 */ .word	0x46000384
/* 000501 0x80AD3344 */ .word	0x45000394
/* 000502 0x80AD3348 */ .word	0x4600039C
/* 000503 0x80AD334C */ .word	0x440004CC
/* 000504 0x80AD3350 */ .word	0x4500054C
/* 000505 0x80AD3354 */ .word	0x46000578
/* 000506 0x80AD3358 */ .word	0x450005C8
/* 000507 0x80AD335C */ .word	0x460005E0
/* 000508 0x80AD3360 */ .word	0x82000010
/* 000509 0x80AD3364 */ .word	0x82000014
/* 000510 0x80AD3368 */ .word	0x82000018
/* 000511 0x80AD336C */ .word	0x8200001C
/* 000512 0x80AD3370 */ .word	0x00000000
/* 000513 0x80AD3374 */ .word	0x00000000
/* 000514 0x80AD3378 */ .word	0x00000000
glabel bgCtowerGearOverlayInfoOffset
/* 000515 0x80AD337C */ .word	0x00000080
