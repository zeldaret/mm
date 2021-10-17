.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Numa_Hana_InitVars
/* 000848 0x80A1B240 */ .word	0x013D0100
/* 000849 0x80A1B244 */ .word	0x00000410
/* 000850 0x80A1B248 */ .word	0x01640000
/* 000851 0x80A1B24C */ .word	0x00000340
/* 000852 0x80A1B250 */ .word	BgNumaHana_Init
/* 000853 0x80A1B254 */ .word	BgNumaHana_Destroy
/* 000854 0x80A1B258 */ .word	BgNumaHana_Update
/* 000855 0x80A1B25C */ .word	BgNumaHana_Draw
glabel D_80A1B260
/* 000856 0x80A1B260 */ .word	0x09000D39
/* 000857 0x80A1B264 */ .word	0x20010000
/* 000858 0x80A1B268 */ .word	0x02000000
/* 000859 0x80A1B26C */ .word	0x00000000
/* 000860 0x80A1B270 */ .word	0x00000000
/* 000861 0x80A1B274 */ .word	0x01CBFBB6
/* 000862 0x80A1B278 */ .word	0x00000000
/* 000863 0x80A1B27C */ .word	0x00050100
/* 000864 0x80A1B280 */ .word	0x00120010
/* 000865 0x80A1B284 */ .word	0x00000000
/* 000866 0x80A1B288 */ .word	0x00000000
glabel D_80A1B28C
/* 000867 0x80A1B28C */ .word	0x3B84B5DD
/* 000868 0x80A1B290 */ .word	0x3D4CCCCD
/* 000869 0x80A1B294 */ .word	0x03010000
/* 000870 0x80A1B298 */ .word	0x00000000
glabel D_80A1B29C
/* 000871 0x80A1B29C */ .word	0x00002AAA
/* 000872 0x80A1B2A0 */ .word	0x55558000
/* 000873 0x80A1B2A4 */ .word	0xAAAAD555
glabel D_80A1B2A8
/* 000874 0x80A1B2A8 */ .word	0xC8580064
/* 000875 0x80A1B2AC */ .word	0xB0FC0FA0
/* 000876 0x80A1B2B0 */ .word	0xB1000320
/* 000877 0x80A1B2B4 */ .word	0x31040258
/* 000878 0x80A1B2B8 */ .word	0x00000000
/* 000879 0x80A1B2BC */ .word	0x00000000
