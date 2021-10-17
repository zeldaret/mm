.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enEncount2OverlayInfo
/* 000640 0x808E1F60 */ .word	0x00000970
/* 000641 0x808E1F64 */ .word	0x00000080
/* 000642 0x808E1F68 */ .word	0x00000010
/* 000643 0x808E1F6C */ .word	0x00000000
/* 000644 0x808E1F70 */ .word	0x00000019
glabel enEncount2OverlayRelocations
/* 000645 0x808E1F74 */ .word	0x4500006C
/* 000646 0x808E1F78 */ .word	0x46000078
/* 000647 0x808E1F7C */ .word	0x450000A0
/* 000648 0x808E1F80 */ .word	0x460000A4
/* 000649 0x808E1F84 */ .word	0x45000110
/* 000650 0x808E1F88 */ .word	0x4600011C
/* 000651 0x808E1F8C */ .word	0x44000138
/* 000652 0x808E1F90 */ .word	0x4500019C
/* 000653 0x808E1F94 */ .word	0x460001A0
/* 000654 0x808E1F98 */ .word	0x450001C8
/* 000655 0x808E1F9C */ .word	0x460001CC
/* 000656 0x808E1FA0 */ .word	0x4500023C
/* 000657 0x808E1FA4 */ .word	0x46000240
/* 000658 0x808E1FA8 */ .word	0x440002F8
/* 000659 0x808E1FAC */ .word	0x45000318
/* 000660 0x808E1FB0 */ .word	0x46000320
/* 000661 0x808E1FB4 */ .word	0x44000400
/* 000662 0x808E1FB8 */ .word	0x440004AC
/* 000663 0x808E1FBC */ .word	0x45000790
/* 000664 0x808E1FC0 */ .word	0x46000794
/* 000665 0x808E1FC4 */ .word	0x82000010
/* 000666 0x808E1FC8 */ .word	0x82000014
/* 000667 0x808E1FCC */ .word	0x82000018
/* 000668 0x808E1FD0 */ .word	0x8200001C
/* 000669 0x808E1FD4 */ .word	0x82000050
/* 000670 0x808E1FD8 */ .word	0x00000000
glabel enEncount2OverlayInfoOffset
/* 000671 0x808E1FDC */ .word	0x00000080
