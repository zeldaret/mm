.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enDoorEtcOverlayInfo
/* 000484 0x80AC2660 */ .word	0x000006B0
/* 000485 0x80AC2664 */ .word	0x000000D0
/* 000486 0x80AC2668 */ .word	0x00000010
/* 000487 0x80AC266C */ .word	0x00000000
/* 000488 0x80AC2670 */ .word	0x0000001B
glabel enDoorEtcOverlayRelocations
/* 000489 0x80AC2674 */ .word	0x4500001C
/* 000490 0x80AC2678 */ .word	0x46000024
/* 000491 0x80AC267C */ .word	0x45000020
/* 000492 0x80AC2680 */ .word	0x46000028
/* 000493 0x80AC2684 */ .word	0x440000E8
/* 000494 0x80AC2688 */ .word	0x450000D8
/* 000495 0x80AC268C */ .word	0x460000F8
/* 000496 0x80AC2690 */ .word	0x45000110
/* 000497 0x80AC2694 */ .word	0x46000114
/* 000498 0x80AC2698 */ .word	0x45000214
/* 000499 0x80AC269C */ .word	0x4600021C
/* 000500 0x80AC26A0 */ .word	0x45000218
/* 000501 0x80AC26A4 */ .word	0x46000220
/* 000502 0x80AC26A8 */ .word	0x45000250
/* 000503 0x80AC26AC */ .word	0x46000254
/* 000504 0x80AC26B0 */ .word	0x450002A0
/* 000505 0x80AC26B4 */ .word	0x460002B0
/* 000506 0x80AC26B8 */ .word	0x4500044C
/* 000507 0x80AC26BC */ .word	0x46000450
/* 000508 0x80AC26C0 */ .word	0x440004CC
/* 000509 0x80AC26C4 */ .word	0x45000514
/* 000510 0x80AC26C8 */ .word	0x46000518
/* 000511 0x80AC26CC */ .word	0x45000600
/* 000512 0x80AC26D0 */ .word	0x46000604
/* 000513 0x80AC26D4 */ .word	0x82000010
/* 000514 0x80AC26D8 */ .word	0x82000014
/* 000515 0x80AC26DC */ .word	0x82000018
/* 000516 0x80AC26E0 */ .word	0x00000000
/* 000517 0x80AC26E4 */ .word	0x00000000
/* 000518 0x80AC26E8 */ .word	0x00000000
glabel enDoorEtcOverlayInfoOffset
/* 000519 0x80AC26EC */ .word	0x00000090
