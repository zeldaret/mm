.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Hata_InitVars
/* 000268 0x8089ED10 */ .word	0x001A0600
/* 000269 0x8089ED14 */ .word	0x00000000
/* 000270 0x8089ED18 */ .word	0x005F0000
/* 000271 0x8089ED1C */ .word	0x000002B0
/* 000272 0x8089ED20 */ .word	EnHata_Init
/* 000273 0x8089ED24 */ .word	EnHata_Destroy
/* 000274 0x8089ED28 */ .word	EnHata_Update
/* 000275 0x8089ED2C */ .word	EnHata_Draw
