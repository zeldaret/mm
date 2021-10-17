.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enRecepgirlOverlayInfo
/* 000452 0x80C106E0 */ .word	0x000006C0
/* 000453 0x80C106E4 */ .word	0x00000040
/* 000454 0x80C106E8 */ .word	0x00000010
/* 000455 0x80C106EC */ .word	0x00000000
/* 000456 0x80C106F0 */ .word	0x0000001E
glabel enRecepgirlOverlayRelocations
/* 000457 0x80C106F4 */ .word	0x4500001C
/* 000458 0x80C106F8 */ .word	0x46000020
/* 000459 0x80C106FC */ .word	0x45000074
/* 000460 0x80C10700 */ .word	0x46000078
/* 000461 0x80C10704 */ .word	0x4500007C
/* 000462 0x80C10708 */ .word	0x46000080
/* 000463 0x80C1070C */ .word	0x45000088
/* 000464 0x80C10710 */ .word	0x4600008C
/* 000465 0x80C10714 */ .word	0x450000A8
/* 000466 0x80C10718 */ .word	0x460000AC
/* 000467 0x80C1071C */ .word	0x440000DC
/* 000468 0x80C10720 */ .word	0x45000140
/* 000469 0x80C10724 */ .word	0x46000144
/* 000470 0x80C10728 */ .word	0x450001B0
/* 000471 0x80C1072C */ .word	0x460001B4
/* 000472 0x80C10730 */ .word	0x44000240
/* 000473 0x80C10734 */ .word	0x450002E8
/* 000474 0x80C10738 */ .word	0x460002EC
/* 000475 0x80C1073C */ .word	0x440003FC
/* 000476 0x80C10740 */ .word	0x4400056C
/* 000477 0x80C10744 */ .word	0x45000660
/* 000478 0x80C10748 */ .word	0x46000670
/* 000479 0x80C1074C */ .word	0x45000664
/* 000480 0x80C10750 */ .word	0x46000674
/* 000481 0x80C10754 */ .word	0x45000678
/* 000482 0x80C10758 */ .word	0x4600068C
/* 000483 0x80C1075C */ .word	0x82000010
/* 000484 0x80C10760 */ .word	0x82000014
/* 000485 0x80C10764 */ .word	0x82000018
/* 000486 0x80C10768 */ .word	0x8200001C
glabel enRecepgirlOverlayInfoOffset
/* 000487 0x80C1076C */ .word	0x00000090
