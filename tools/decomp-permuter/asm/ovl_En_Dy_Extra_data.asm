.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Dy_Extra_InitVars
/* 000284 0x80A61720 */ .word	0x01750600
/* 000285 0x80A61724 */ .word	0x00000030
/* 000286 0x80A61728 */ .word	0x00080000
/* 000287 0x80A6172C */ .word	0x0000016C
/* 000288 0x80A61730 */ .word	EnDyExtra_Init
/* 000289 0x80A61734 */ .word	EnDyExtra_Destroy
/* 000290 0x80A61738 */ .word	EnDyExtra_Update
/* 000291 0x80A6173C */ .word	EnDyExtra_Draw
glabel D_80A61740
/* 000292 0x80A61740 */ .word	0xFFFFAAFF
/* 000293 0x80A61744 */ .word	0xFFAAFFFF
/* 000294 0x80A61748 */ .word	0xFFFFAAFF
/* 000295 0x80A6174C */ .word	0xAAFFFFFF
/* 000296 0x80A61750 */ .word	0xFFFFAAFF
glabel D_80A61754
/* 000297 0x80A61754 */ .word	0xFF6400FF
/* 000298 0x80A61758 */ .word	0xFF0064FF
/* 000299 0x80A6175C */ .word	0x64FF00FF
/* 000300 0x80A61760 */ .word	0x0064FFFF
/* 000301 0x80A61764 */ .word	0xFFE600FF
glabel D_80A61768
/* 000302 0x80A61768 */ .word	0x02010102
/* 000303 0x80A6176C */ .word	0x00000201
/* 000304 0x80A61770 */ .word	0x00020100
/* 000305 0x80A61774 */ .word	0x02010002
/* 000306 0x80A61778 */ .word	0x01000201
/* 000307 0x80A6177C */ .word	0x00020100
/* 000308 0x80A61780 */ .word	0x01020000
/* 000309 0x80A61784 */ .word	0x00000000
/* 000310 0x80A61788 */ .word	0x00000000
/* 000311 0x80A6178C */ .word	0x00000000
