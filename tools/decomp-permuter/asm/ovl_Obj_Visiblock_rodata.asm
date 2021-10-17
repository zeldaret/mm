.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objVisiblockOverlayInfo
/* 000060 0x80ADEB60 */ .word	0x000000C0
/* 000061 0x80ADEB64 */ .word	0x00000030
/* 000062 0x80ADEB68 */ .word	0x00000000
/* 000063 0x80ADEB6C */ .word	0x00000000
/* 000064 0x80ADEB70 */ .word	0x00000005
glabel objVisiblockOverlayRelocations
/* 000065 0x80ADEB74 */ .word	0x45000010
/* 000066 0x80ADEB78 */ .word	0x46000014
/* 000067 0x80ADEB7C */ .word	0x82000010
/* 000068 0x80ADEB80 */ .word	0x82000014
/* 000069 0x80ADEB84 */ .word	0x8200001C
/* 000070 0x80ADEB88 */ .word	0x00000000
glabel objVisiblockOverlayInfoOffset
/* 000071 0x80ADEB8C */ .word	0x00000030
