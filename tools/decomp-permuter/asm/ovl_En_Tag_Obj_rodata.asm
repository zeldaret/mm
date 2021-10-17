.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enTagObjOverlayInfo
/* 000056 0x80B12950 */ .word	0x00000090
/* 000057 0x80B12954 */ .word	0x00000050
/* 000058 0x80B12958 */ .word	0x00000000
/* 000059 0x80B1295C */ .word	0x00000000
/* 000060 0x80B12960 */ .word	0x00000003
glabel enTagObjOverlayRelocations
/* 000061 0x80B12964 */ .word	0x8200003C
/* 000062 0x80B12968 */ .word	0x82000040
/* 000063 0x80B1296C */ .word	0x82000044
/* 000064 0x80B12970 */ .word	0x00000000
/* 000065 0x80B12974 */ .word	0x00000000
/* 000066 0x80B12978 */ .word	0x00000000
glabel enTagObjOverlayInfoOffset
/* 000067 0x80B1297C */ .word	0x00000030
