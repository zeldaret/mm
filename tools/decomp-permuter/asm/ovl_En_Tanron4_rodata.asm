.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enTanron4OverlayInfo
/* 000848 0x80BE48C0 */ .word	0x00000D00
/* 000849 0x80BE48C4 */ .word	0x00000020
/* 000850 0x80BE48C8 */ .word	0x00000020
/* 000851 0x80BE48CC */ .word	0x00000000
/* 000852 0x80BE48D0 */ .word	0x00000016
glabel enTanron4OverlayRelocations
/* 000853 0x80BE48D4 */ .word	0x45000094
/* 000854 0x80BE48D8 */ .word	0x460000B0
/* 000855 0x80BE48DC */ .word	0x440000F0
/* 000856 0x80BE48E0 */ .word	0x44000100
/* 000857 0x80BE48E4 */ .word	0x450001E4
/* 000858 0x80BE48E8 */ .word	0x460001E8
/* 000859 0x80BE48EC */ .word	0x4500024C
/* 000860 0x80BE48F0 */ .word	0x46000250
/* 000861 0x80BE48F4 */ .word	0x450005C4
/* 000862 0x80BE48F8 */ .word	0x460005C8
/* 000863 0x80BE48FC */ .word	0x450006F4
/* 000864 0x80BE4900 */ .word	0x460006F8
/* 000865 0x80BE4904 */ .word	0x45000A90
/* 000866 0x80BE4908 */ .word	0x46000A94
/* 000867 0x80BE490C */ .word	0x45000BD0
/* 000868 0x80BE4910 */ .word	0x46000BD4
/* 000869 0x80BE4914 */ .word	0x45000BDC
/* 000870 0x80BE4918 */ .word	0x46000BE0
/* 000871 0x80BE491C */ .word	0x82000010
/* 000872 0x80BE4920 */ .word	0x82000014
/* 000873 0x80BE4924 */ .word	0x82000018
/* 000874 0x80BE4928 */ .word	0x8200001C
glabel enTanron4OverlayInfoOffset
/* 000875 0x80BE492C */ .word	0x00000070
