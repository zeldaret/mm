.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Kin2_Shelf_InitVars
/* 000768 0x80B70730 */ .word	0x02110100
/* 000769 0x80B70734 */ .word	0x00000000
/* 000770 0x80B70738 */ .word	0x01F50000
/* 000771 0x80B7073C */ .word	0x00000168
/* 000772 0x80B70740 */ .word	BgKin2Shelf_Init
/* 000773 0x80B70744 */ .word	BgKin2Shelf_Destroy
/* 000774 0x80B70748 */ .word	BgKin2Shelf_Update
/* 000775 0x80B7074C */ .word	BgKin2Shelf_Draw
glabel D_80B70750
/* 000776 0x80B70750 */ .word	0x42700000
/* 000777 0x80B70754 */ .word	0x42F00000
glabel D_80B70758
/* 000778 0x80B70758 */ .word	0x42200000
/* 000779 0x80B7075C */ .word	0x00000000
glabel D_80B70760
/* 000780 0x80B70760 */ .word	0x41200000
/* 000781 0x80B70764 */ .word	0x41700000
glabel D_80B70768
/* 000782 0x80B70768 */ .word	0x41700000
/* 000783 0x80B7076C */ .word	0x42700000
glabel D_80B70770
/* 000784 0x80B70770 */ .word	0x41200000
/* 000785 0x80B70774 */ .word	0x41700000
glabel D_80B70778
/* 000786 0x80B70778 */ .word	0x0F0A0000
glabel D_80B7077C
/* 000787 0x80B7077C */ .word	0x30FC0FA0
glabel D_80B70780
/* 000788 0x80B70780 */ .word	0x06001328
/* 000789 0x80B70784 */ .word	0x06000F80
glabel D_80B70788
/* 000790 0x80B70788 */ .word	0x060010F8
/* 000791 0x80B7078C */ .word	0x06000CA8
