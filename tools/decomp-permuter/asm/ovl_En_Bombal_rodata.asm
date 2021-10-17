.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enBombalOverlayInfo
/* 000652 0x80C064A0 */ .word	0x000009D0
/* 000653 0x80C064A4 */ .word	0x00000050
/* 000654 0x80C064A8 */ .word	0x00000010
/* 000655 0x80C064AC */ .word	0x00000000
/* 000656 0x80C064B0 */ .word	0x00000016
glabel enBombalOverlayRelocations
/* 000657 0x80C064B4 */ .word	0x45000030
/* 000658 0x80C064B8 */ .word	0x46000034
/* 000659 0x80C064BC */ .word	0x45000058
/* 000660 0x80C064C0 */ .word	0x4600005C
/* 000661 0x80C064C4 */ .word	0x4400006C
/* 000662 0x80C064C8 */ .word	0x450000B4
/* 000663 0x80C064CC */ .word	0x460000B8
/* 000664 0x80C064D0 */ .word	0x450000E0
/* 000665 0x80C064D4 */ .word	0x460000E4
/* 000666 0x80C064D8 */ .word	0x45000178
/* 000667 0x80C064DC */ .word	0x460001B8
/* 000668 0x80C064E0 */ .word	0x4400030C
/* 000669 0x80C064E4 */ .word	0x45000340
/* 000670 0x80C064E8 */ .word	0x4600034C
/* 000671 0x80C064EC */ .word	0x44000470
/* 000672 0x80C064F0 */ .word	0x44000508
/* 000673 0x80C064F4 */ .word	0x450007EC
/* 000674 0x80C064F8 */ .word	0x460007F0
/* 000675 0x80C064FC */ .word	0x82000010
/* 000676 0x80C06500 */ .word	0x82000014
/* 000677 0x80C06504 */ .word	0x82000018
/* 000678 0x80C06508 */ .word	0x8200001C
glabel enBombalOverlayInfoOffset
/* 000679 0x80C0650C */ .word	0x00000070
