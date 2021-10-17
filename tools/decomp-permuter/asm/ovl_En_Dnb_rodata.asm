.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enDnbOverlayInfo
/* 000964 0x80A50CE0 */ .word	0x00000EC0
/* 000965 0x80A50CE4 */ .word	0x00000050
/* 000966 0x80A50CE8 */ .word	0x00000000
/* 000967 0x80A50CEC */ .word	0x00000000
/* 000968 0x80A50CF0 */ .word	0x00000011
glabel enDnbOverlayRelocations
/* 000969 0x80A50CF4 */ .word	0x450003A8
/* 000970 0x80A50CF8 */ .word	0x460003B0
/* 000971 0x80A50CFC */ .word	0x44000470
/* 000972 0x80A50D00 */ .word	0x4400053C
/* 000973 0x80A50D04 */ .word	0x4400062C
/* 000974 0x80A50D08 */ .word	0x440006E0
/* 000975 0x80A50D0C */ .word	0x440006F8
/* 000976 0x80A50D10 */ .word	0x44000718
/* 000977 0x80A50D14 */ .word	0x440009B8
/* 000978 0x80A50D18 */ .word	0x440009C8
/* 000979 0x80A50D1C */ .word	0x440009D8
/* 000980 0x80A50D20 */ .word	0x45000DC8
/* 000981 0x80A50D24 */ .word	0x46000E30
/* 000982 0x80A50D28 */ .word	0x82000010
/* 000983 0x80A50D2C */ .word	0x82000014
/* 000984 0x80A50D30 */ .word	0x82000018
/* 000985 0x80A50D34 */ .word	0x8200001C
/* 000986 0x80A50D38 */ .word	0x00000000
glabel enDnbOverlayInfoOffset
/* 000987 0x80A50D3C */ .word	0x00000060
