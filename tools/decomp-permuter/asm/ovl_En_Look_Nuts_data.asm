.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Look_Nuts_InitVars
/* 000844 0x80A685E0 */ .word	0x017A0400
/* 000845 0x80A685E4 */ .word	0x80000000
/* 000846 0x80A685E8 */ .word	0x01350000
/* 000847 0x80A685EC */ .word	0x00000290
/* 000848 0x80A685F0 */ .word	EnLookNuts_Init
/* 000849 0x80A685F4 */ .word	EnLookNuts_Destroy
/* 000850 0x80A685F8 */ .word	EnLookNuts_Update
/* 000851 0x80A685FC */ .word	EnLookNuts_Draw
glabel D_80A68600
/* 000852 0x80A68600 */ .word	0x0A000900
/* 000853 0x80A68604 */ .word	0x00010000
/* 000854 0x80A68608 */ .word	0x00000000
/* 000855 0x80A6860C */ .word	0xF7CFFFFF
/* 000856 0x80A68610 */ .word	0x00000000
/* 000857 0x80A68614 */ .word	0xF7CFFFFF
/* 000858 0x80A68618 */ .word	0x00000000
/* 000859 0x80A6861C */ .word	0x00010000
/* 000860 0x80A68620 */ .word	0x00140032
/* 000861 0x80A68624 */ .word	0x00000000
/* 000862 0x80A68628 */ .word	0x00000000
glabel D_80A6862C
/* 000863 0x80A6862C */ .word	0x00000000
glabel D_80A68630
/* 000864 0x80A68630 */ .word	0xF1F1F1F1
/* 000865 0x80A68634 */ .word	0xF1F1F1E1
/* 000866 0x80A68638 */ .word	0xF1F1F1F1
/* 000867 0x80A6863C */ .word	0xF1F1F1F1
/* 000868 0x80A68640 */ .word	0xF1F1F1F1
/* 000869 0x80A68644 */ .word	0x0000F1F1
/* 000870 0x80A68648 */ .word	0xF1F1F0F0
/* 000871 0x80A6864C */ .word	0xF000F1F1
glabel D_80A68650
/* 000872 0x80A68650 */ .word	0x00000000
/* 000873 0x80A68654 */ .word	0x00000000
/* 000874 0x80A68658 */ .word	0x00000000
glabel D_80A6865C
/* 000875 0x80A6865C */ .word	0x06001680
/* 000876 0x80A68660 */ .word	0x06001700
/* 000877 0x80A68664 */ .word	0x06001780
/* 000878 0x80A68668 */ .word	0x00000000
/* 000879 0x80A6866C */ .word	0x00000000
