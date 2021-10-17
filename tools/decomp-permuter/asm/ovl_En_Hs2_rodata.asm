.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enHs2OverlayInfo
/* 000044 0x8098F010 */ .word	0x00000090
/* 000045 0x8098F014 */ .word	0x00000020
/* 000046 0x8098F018 */ .word	0x00000000
/* 000047 0x8098F01C */ .word	0x00000000
/* 000048 0x8098F020 */ .word	0x00000006
glabel enHs2OverlayRelocations
/* 000049 0x8098F024 */ .word	0x45000020
/* 000050 0x8098F028 */ .word	0x46000024
/* 000051 0x8098F02C */ .word	0x82000010
/* 000052 0x8098F030 */ .word	0x82000014
/* 000053 0x8098F034 */ .word	0x82000018
/* 000054 0x8098F038 */ .word	0x8200001C
glabel enHs2OverlayInfoOffset
/* 000055 0x8098F03C */ .word	0x00000030
