.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objUsiyaneOverlayInfo
/* 000660 0x80C086D0 */ .word	0x000009C0
/* 000661 0x80C086D4 */ .word	0x00000080
/* 000662 0x80C086D8 */ .word	0x00000010
/* 000663 0x80C086DC */ .word	0x00000000
/* 000664 0x80C086E0 */ .word	0x0000001E
glabel objUsiyaneOverlayRelocations
/* 000665 0x80C086E4 */ .word	0x440000D0
/* 000666 0x80C086E8 */ .word	0x44000154
/* 000667 0x80C086EC */ .word	0x45000308
/* 000668 0x80C086F0 */ .word	0x4600030C
/* 000669 0x80C086F4 */ .word	0x45000310
/* 000670 0x80C086F8 */ .word	0x46000324
/* 000671 0x80C086FC */ .word	0x4400038C
/* 000672 0x80C08700 */ .word	0x4500039C
/* 000673 0x80C08704 */ .word	0x460003A8
/* 000674 0x80C08708 */ .word	0x440003B8
/* 000675 0x80C0870C */ .word	0x45000574
/* 000676 0x80C08710 */ .word	0x46000578
/* 000677 0x80C08714 */ .word	0x440006C4
/* 000678 0x80C08718 */ .word	0x450006CC
/* 000679 0x80C0871C */ .word	0x460006D0
/* 000680 0x80C08720 */ .word	0x45000700
/* 000681 0x80C08724 */ .word	0x46000704
/* 000682 0x80C08728 */ .word	0x45000748
/* 000683 0x80C0872C */ .word	0x46000758
/* 000684 0x80C08730 */ .word	0x44000774
/* 000685 0x80C08734 */ .word	0x4500077C
/* 000686 0x80C08738 */ .word	0x46000780
/* 000687 0x80C0873C */ .word	0x45000864
/* 000688 0x80C08740 */ .word	0x46000870
/* 000689 0x80C08744 */ .word	0x450008E0
/* 000690 0x80C08748 */ .word	0x460008EC
/* 000691 0x80C0874C */ .word	0x82000010
/* 000692 0x80C08750 */ .word	0x82000014
/* 000693 0x80C08754 */ .word	0x82000018
/* 000694 0x80C08758 */ .word	0x8200001C
glabel objUsiyaneOverlayInfoOffset
/* 000695 0x80C0875C */ .word	0x00000090
