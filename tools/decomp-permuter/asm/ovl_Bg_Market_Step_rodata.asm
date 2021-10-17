.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgMarketStepOverlayInfo
/* 000052 0x80AF0130 */ .word	0x00000090
/* 000053 0x80AF0134 */ .word	0x00000040
/* 000054 0x80AF0138 */ .word	0x00000000
/* 000055 0x80AF013C */ .word	0x00000000
/* 000056 0x80AF0140 */ .word	0x00000008
glabel bgMarketStepOverlayRelocations
/* 000057 0x80AF0144 */ .word	0x4500000C
/* 000058 0x80AF0148 */ .word	0x46000014
/* 000059 0x80AF014C */ .word	0x4500003C
/* 000060 0x80AF0150 */ .word	0x46000050
/* 000061 0x80AF0154 */ .word	0x45000060
/* 000062 0x80AF0158 */ .word	0x46000070
/* 000063 0x80AF015C */ .word	0x82000010
/* 000064 0x80AF0160 */ .word	0x8200001C
/* 000065 0x80AF0164 */ .word	0x00000000
/* 000066 0x80AF0168 */ .word	0x00000000
glabel bgMarketStepOverlayInfoOffset
/* 000067 0x80AF016C */ .word	0x00000040
