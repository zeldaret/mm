.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgHakaBombwallOverlayInfo
/* 000448 0x80BD6500 */ .word	0x00000680
/* 000449 0x80BD6504 */ .word	0x00000070
/* 000450 0x80BD6508 */ .word	0x00000010
/* 000451 0x80BD650C */ .word	0x00000000
/* 000452 0x80BD6510 */ .word	0x00000017
glabel bgHakaBombwallOverlayRelocations
/* 000453 0x80BD6514 */ .word	0x45000184
/* 000454 0x80BD6518 */ .word	0x46000188
/* 000455 0x80BD651C */ .word	0x45000284
/* 000456 0x80BD6520 */ .word	0x4600028C
/* 000457 0x80BD6524 */ .word	0x45000374
/* 000458 0x80BD6528 */ .word	0x46000378
/* 000459 0x80BD652C */ .word	0x450003D8
/* 000460 0x80BD6530 */ .word	0x460003DC
/* 000461 0x80BD6534 */ .word	0x440003FC
/* 000462 0x80BD6538 */ .word	0x45000460
/* 000463 0x80BD653C */ .word	0x46000464
/* 000464 0x80BD6540 */ .word	0x44000488
/* 000465 0x80BD6544 */ .word	0x4400049C
/* 000466 0x80BD6548 */ .word	0x450004F8
/* 000467 0x80BD654C */ .word	0x460004FC
/* 000468 0x80BD6550 */ .word	0x44000548
/* 000469 0x80BD6554 */ .word	0x44000588
/* 000470 0x80BD6558 */ .word	0x450005B4
/* 000471 0x80BD655C */ .word	0x460005BC
/* 000472 0x80BD6560 */ .word	0x82000010
/* 000473 0x80BD6564 */ .word	0x82000014
/* 000474 0x80BD6568 */ .word	0x82000018
/* 000475 0x80BD656C */ .word	0x8200001C
/* 000476 0x80BD6570 */ .word	0x00000000
/* 000477 0x80BD6574 */ .word	0x00000000
/* 000478 0x80BD6578 */ .word	0x00000000
glabel bgHakaBombwallOverlayInfoOffset
/* 000479 0x80BD657C */ .word	0x00000080
