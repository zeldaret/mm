.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objSyokudaiOverlayInfo
/* 000848 0x808BCD50 */ .word	0x00000C90
/* 000849 0x808BCD54 */ .word	0x000000A0
/* 000850 0x808BCD58 */ .word	0x00000010
/* 000851 0x808BCD5C */ .word	0x00000010
/* 000852 0x808BCD60 */ .word	0x0000001C
glabel objSyokudaiOverlayRelocations
/* 000853 0x808BCD64 */ .word	0x4500001C
/* 000854 0x808BCD68 */ .word	0x46000020
/* 000855 0x808BCD6C */ .word	0x45000064
/* 000856 0x808BCD70 */ .word	0x46000068
/* 000857 0x808BCD74 */ .word	0x45000080
/* 000858 0x808BCD78 */ .word	0x46000090
/* 000859 0x808BCD7C */ .word	0x45000084
/* 000860 0x808BCD80 */ .word	0x46000094
/* 000861 0x808BCD84 */ .word	0x4500018C
/* 000862 0x808BCD88 */ .word	0x46000190
/* 000863 0x808BCD8C */ .word	0x4500019C
/* 000864 0x808BCD90 */ .word	0x460001A0
/* 000865 0x808BCD94 */ .word	0x45000688
/* 000866 0x808BCD98 */ .word	0x460006E0
/* 000867 0x808BCD9C */ .word	0x450006E4
/* 000868 0x808BCDA0 */ .word	0x460006F0
/* 000869 0x808BCDA4 */ .word	0x450007CC
/* 000870 0x808BCDA8 */ .word	0x460007D0
/* 000871 0x808BCDAC */ .word	0x4500090C
/* 000872 0x808BCDB0 */ .word	0x46000910
/* 000873 0x808BCDB4 */ .word	0x45000A38
/* 000874 0x808BCDB8 */ .word	0x46000A58
/* 000875 0x808BCDBC */ .word	0x45000ADC
/* 000876 0x808BCDC0 */ .word	0x46000AE0
/* 000877 0x808BCDC4 */ .word	0x82000010
/* 000878 0x808BCDC8 */ .word	0x82000014
/* 000879 0x808BCDCC */ .word	0x82000018
/* 000880 0x808BCDD0 */ .word	0x8200001C
/* 000881 0x808BCDD4 */ .word	0x00000000
/* 000882 0x808BCDD8 */ .word	0x00000000
glabel objSyokudaiOverlayInfoOffset
/* 000883 0x808BCDDC */ .word	0x00000090
