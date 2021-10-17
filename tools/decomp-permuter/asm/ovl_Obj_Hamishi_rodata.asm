.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objHamishiOverlayInfo
/* 000768 0x809A1B20 */ .word	0x00000B60
/* 000769 0x809A1B24 */ .word	0x00000080
/* 000770 0x809A1B28 */ .word	0x00000020
/* 000771 0x809A1B2C */ .word	0x00000000
/* 000772 0x809A1B30 */ .word	0x0000001B
glabel objHamishiOverlayRelocations
/* 000773 0x809A1B34 */ .word	0x45000024
/* 000774 0x809A1B38 */ .word	0x4600002C
/* 000775 0x809A1B3C */ .word	0x4500023C
/* 000776 0x809A1B40 */ .word	0x46000250
/* 000777 0x809A1B44 */ .word	0x45000578
/* 000778 0x809A1B48 */ .word	0x4600057C
/* 000779 0x809A1B4C */ .word	0x440005D8
/* 000780 0x809A1B50 */ .word	0x450005E0
/* 000781 0x809A1B54 */ .word	0x460005E4
/* 000782 0x809A1B58 */ .word	0x440005F8
/* 000783 0x809A1B5C */ .word	0x44000650
/* 000784 0x809A1B60 */ .word	0x440006D0
/* 000785 0x809A1B64 */ .word	0x44000794
/* 000786 0x809A1B68 */ .word	0x450008A8
/* 000787 0x809A1B6C */ .word	0x460008AC
/* 000788 0x809A1B70 */ .word	0x450008D0
/* 000789 0x809A1B74 */ .word	0x460008E0
/* 000790 0x809A1B78 */ .word	0x450009B0
/* 000791 0x809A1B7C */ .word	0x460009B4
/* 000792 0x809A1B80 */ .word	0x450009B8
/* 000793 0x809A1B84 */ .word	0x460009D0
/* 000794 0x809A1B88 */ .word	0x450009D4
/* 000795 0x809A1B8C */ .word	0x460009D8
/* 000796 0x809A1B90 */ .word	0x82000010
/* 000797 0x809A1B94 */ .word	0x82000014
/* 000798 0x809A1B98 */ .word	0x82000018
/* 000799 0x809A1B9C */ .word	0x8200001C
/* 000800 0x809A1BA0 */ .word	0x00000000
/* 000801 0x809A1BA4 */ .word	0x00000000
/* 000802 0x809A1BA8 */ .word	0x00000000
glabel objHamishiOverlayInfoOffset
/* 000803 0x809A1BAC */ .word	0x00000090
