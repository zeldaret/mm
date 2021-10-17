.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enTanron1OverlayInfo
/* 001616 0x80BB6740 */ .word	0x00001000
/* 001617 0x80BB6744 */ .word	0x00000920
/* 001618 0x80BB6748 */ .word	0x00000020
/* 001619 0x80BB674C */ .word	0x00000000
/* 001620 0x80BB6750 */ .word	0x0000001E
glabel enTanron1OverlayRelocations
/* 001621 0x80BB6754 */ .word	0x440001EC
/* 001622 0x80BB6758 */ .word	0x44000268
/* 001623 0x80BB675C */ .word	0x440004D8
/* 001624 0x80BB6760 */ .word	0x44000500
/* 001625 0x80BB6764 */ .word	0x45000594
/* 001626 0x80BB6768 */ .word	0x4600059C
/* 001627 0x80BB676C */ .word	0x450005D0
/* 001628 0x80BB6770 */ .word	0x460005DC
/* 001629 0x80BB6774 */ .word	0x45000684
/* 001630 0x80BB6778 */ .word	0x46000688
/* 001631 0x80BB677C */ .word	0x450008F8
/* 001632 0x80BB6780 */ .word	0x460008FC
/* 001633 0x80BB6784 */ .word	0x45000D08
/* 001634 0x80BB6788 */ .word	0x46000D14
/* 001635 0x80BB678C */ .word	0x45000D20
/* 001636 0x80BB6790 */ .word	0x46000D30
/* 001637 0x80BB6794 */ .word	0x45000D34
/* 001638 0x80BB6798 */ .word	0x46000D38
/* 001639 0x80BB679C */ .word	0x45000E20
/* 001640 0x80BB67A0 */ .word	0x46000E30
/* 001641 0x80BB67A4 */ .word	0x45000E34
/* 001642 0x80BB67A8 */ .word	0x46000E40
/* 001643 0x80BB67AC */ .word	0x45000E38
/* 001644 0x80BB67B0 */ .word	0x46000E3C
/* 001645 0x80BB67B4 */ .word	0x82000010
/* 001646 0x80BB67B8 */ .word	0x82000014
/* 001647 0x80BB67BC */ .word	0x82000018
/* 001648 0x80BB67C0 */ .word	0x8200001C
/* 001649 0x80BB67C4 */ .word	0x820008B4
/* 001650 0x80BB67C8 */ .word	0x82000904
glabel enTanron1OverlayInfoOffset
/* 001651 0x80BB67CC */ .word	0x00000090
