.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_F40_Flift_InitVars
/* 000176 0x808D7810 */ .word	0x004D0100
/* 000177 0x808D7814 */ .word	0x00000010
/* 000178 0x808D7818 */ .word	0x005C0000
/* 000179 0x808D781C */ .word	0x00000164
/* 000180 0x808D7820 */ .word	BgF40Flift_Init
/* 000181 0x808D7824 */ .word	BgF40Flift_Destroy
/* 000182 0x808D7828 */ .word	BgF40Flift_Update
/* 000183 0x808D782C */ .word	BgF40Flift_Draw
glabel D_808D7830
/* 000184 0x808D7830 */ .word	0xB1000190
/* 000185 0x808D7834 */ .word	0xB0FC1388
/* 000186 0x808D7838 */ .word	0x48580064
/* 000187 0x808D783C */ .word	0x00000000
