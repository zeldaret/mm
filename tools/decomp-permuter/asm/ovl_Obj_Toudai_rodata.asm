.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_80A34670
/* 000732 0x80A34670 */ .word	0x3DCCCCCD
glabel D_80A34674
/* 000733 0x80A34674 */ .word	0x3FE66666
glabel D_80A34678
/* 000734 0x80A34678 */ .word	0x3F19999A
glabel D_80A3467C
/* 000735 0x80A3467C */ .word	0x3DCCCCCD
glabel objToudaiOverlayInfo
/* 000736 0x80A34680 */ .word	0x00000A70
/* 000737 0x80A34684 */ .word	0x00000100
/* 000738 0x80A34688 */ .word	0x00000010
/* 000739 0x80A3468C */ .word	0x00000000
/* 000740 0x80A34690 */ .word	0x00000019
glabel objToudaiOverlayRelocations
/* 000741 0x80A34694 */ .word	0x45000020
/* 000742 0x80A34698 */ .word	0x46000024
/* 000743 0x80A3469C */ .word	0x450000D0
/* 000744 0x80A346A0 */ .word	0x460000D4
/* 000745 0x80A346A4 */ .word	0x450000DC
/* 000746 0x80A346A8 */ .word	0x460000F8
/* 000747 0x80A346AC */ .word	0x45000108
/* 000748 0x80A346B0 */ .word	0x46000264
/* 000749 0x80A346B4 */ .word	0x4500010C
/* 000750 0x80A346B8 */ .word	0x46000318
/* 000751 0x80A346BC */ .word	0x450000EC
/* 000752 0x80A346C0 */ .word	0x460000F0
/* 000753 0x80A346C4 */ .word	0x450003CC
/* 000754 0x80A346C8 */ .word	0x460003D0
/* 000755 0x80A346CC */ .word	0x450006D0
/* 000756 0x80A346D0 */ .word	0x460006D4
/* 000757 0x80A346D4 */ .word	0x45000948
/* 000758 0x80A346D8 */ .word	0x4600094C
/* 000759 0x80A346DC */ .word	0x44000990
/* 000760 0x80A346E0 */ .word	0x44000A4C
/* 000761 0x80A346E4 */ .word	0x44000A58
/* 000762 0x80A346E8 */ .word	0x82000010
/* 000763 0x80A346EC */ .word	0x82000014
/* 000764 0x80A346F0 */ .word	0x82000018
/* 000765 0x80A346F4 */ .word	0x8200001C
/* 000766 0x80A346F8 */ .word	0x00000000
glabel objToudaiOverlayInfoOffset
/* 000767 0x80A346FC */ .word	0x00000080
