.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objDinnerOverlayInfo
/* 000084 0x80BEBA90 */ .word	0x00000130
/* 000085 0x80BEBA94 */ .word	0x00000020
/* 000086 0x80BEBA98 */ .word	0x00000000
/* 000087 0x80BEBA9C */ .word	0x00000000
/* 000088 0x80BEBAA0 */ .word	0x00000004
glabel objDinnerOverlayRelocations
/* 000089 0x80BEBAA4 */ .word	0x82000010
/* 000090 0x80BEBAA8 */ .word	0x82000014
/* 000091 0x80BEBAAC */ .word	0x82000018
/* 000092 0x80BEBAB0 */ .word	0x8200001C
/* 000093 0x80BEBAB4 */ .word	0x00000000
/* 000094 0x80BEBAB8 */ .word	0x00000000
glabel objDinnerOverlayInfoOffset
/* 000095 0x80BEBABC */ .word	0x00000030
