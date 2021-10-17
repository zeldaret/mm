.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_8097F810
/* 000464 0x8097F810 */ .word	0x0000001B
/* 000465 0x8097F814 */ .word	func_8097F0D0
/* 000466 0x8097F818 */ .word	0x00000000
/* 000467 0x8097F81C */ .word	0x00000000
glabel D_8097F820
/* 000468 0x8097F820 */ .word	0x3C23D70A
glabel D_8097F824
/* 000469 0x8097F824 */ .word	0x477FFF00
/* 000470 0x8097F828 */ .word	0x00000000
/* 000471 0x8097F82C */ .word	0x00000000
glabel effectSsEnIceOverlayInfo
/* 000472 0x8097F830 */ .word	0x00000740
/* 000473 0x8097F834 */ .word	0x00000010
/* 000474 0x8097F838 */ .word	0x00000010
/* 000475 0x8097F83C */ .word	0x00000000
/* 000476 0x8097F840 */ .word	0x0000000D
glabel effectSsEnIceOverlayRelocations
/* 000477 0x8097F844 */ .word	0x45000094
/* 000478 0x8097F848 */ .word	0x4600009C
/* 000479 0x8097F84C */ .word	0x45000098
/* 000480 0x8097F850 */ .word	0x460000A0
/* 000481 0x8097F854 */ .word	0x45000168
/* 000482 0x8097F858 */ .word	0x46000170
/* 000483 0x8097F85C */ .word	0x4500016C
/* 000484 0x8097F860 */ .word	0x46000174
/* 000485 0x8097F864 */ .word	0x4500023C
/* 000486 0x8097F868 */ .word	0x46000240
/* 000487 0x8097F86C */ .word	0x4500067C
/* 000488 0x8097F870 */ .word	0x46000684
/* 000489 0x8097F874 */ .word	0x82000004
/* 000490 0x8097F878 */ .word	0x00000000
glabel effectSsEnIceOverlayInfoOffset
/* 000491 0x8097F87C */ .word	0x00000050
