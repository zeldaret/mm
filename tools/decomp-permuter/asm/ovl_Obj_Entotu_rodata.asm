.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objEntotuOverlayInfo
/* 000868 0x80A35490 */ .word	0x00000CF0
/* 000869 0x80A35494 */ .word	0x00000090
/* 000870 0x80A35498 */ .word	0x00000010
/* 000871 0x80A3549C */ .word	0x00000000
/* 000872 0x80A354A0 */ .word	0x0000001A
glabel objEntotuOverlayRelocations
/* 000873 0x80A354A4 */ .word	0x440002D0
/* 000874 0x80A354A8 */ .word	0x4500039C
/* 000875 0x80A354AC */ .word	0x460003A0
/* 000876 0x80A354B0 */ .word	0x45000448
/* 000877 0x80A354B4 */ .word	0x4600044C
/* 000878 0x80A354B8 */ .word	0x45000454
/* 000879 0x80A354BC */ .word	0x46000470
/* 000880 0x80A354C0 */ .word	0x45000478
/* 000881 0x80A354C4 */ .word	0x460005E4
/* 000882 0x80A354C8 */ .word	0x45000514
/* 000883 0x80A354CC */ .word	0x46000690
/* 000884 0x80A354D0 */ .word	0x450005A0
/* 000885 0x80A354D4 */ .word	0x4600073C
/* 000886 0x80A354D8 */ .word	0x45000594
/* 000887 0x80A354DC */ .word	0x46000598
/* 000888 0x80A354E0 */ .word	0x45000B08
/* 000889 0x80A354E4 */ .word	0x46000B0C
/* 000890 0x80A354E8 */ .word	0x45000C40
/* 000891 0x80A354EC */ .word	0x46000C44
/* 000892 0x80A354F0 */ .word	0x44000C94
/* 000893 0x80A354F4 */ .word	0x44000CC0
/* 000894 0x80A354F8 */ .word	0x44000CCC
/* 000895 0x80A354FC */ .word	0x82000010
/* 000896 0x80A35500 */ .word	0x82000014
/* 000897 0x80A35504 */ .word	0x82000018
/* 000898 0x80A35508 */ .word	0x8200001C
glabel objEntotuOverlayInfoOffset
/* 000899 0x80A3550C */ .word	0x00000080
