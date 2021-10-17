.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objEndingOverlayInfo
/* 000080 0x80C25D00 */ .word	0x00000100
/* 000081 0x80C25D04 */ .word	0x00000040
/* 000082 0x80C25D08 */ .word	0x00000000
/* 000083 0x80C25D0C */ .word	0x00000000
/* 000084 0x80C25D10 */ .word	0x00000007
glabel objEndingOverlayRelocations
/* 000085 0x80C25D14 */ .word	0x45000010
/* 000086 0x80C25D18 */ .word	0x46000014
/* 000087 0x80C25D1C */ .word	0x45000028
/* 000088 0x80C25D20 */ .word	0x4600002C
/* 000089 0x80C25D24 */ .word	0x82000010
/* 000090 0x80C25D28 */ .word	0x82000018
/* 000091 0x80C25D2C */ .word	0x8200001C
/* 000092 0x80C25D30 */ .word	0x00000000
/* 000093 0x80C25D34 */ .word	0x00000000
/* 000094 0x80C25D38 */ .word	0x00000000
glabel objEndingOverlayInfoOffset
/* 000095 0x80C25D3C */ .word	0x00000040
