.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enScopecoinOverlayInfo
/* 000192 0x80BFD2A0 */ .word	0x000002C0
/* 000193 0x80BFD2A4 */ .word	0x00000040
/* 000194 0x80BFD2A8 */ .word	0x00000000
/* 000195 0x80BFD2AC */ .word	0x00000000
/* 000196 0x80BFD2B0 */ .word	0x0000000A
glabel enScopecoinOverlayRelocations
/* 000197 0x80BFD2B4 */ .word	0x45000130
/* 000198 0x80BFD2B8 */ .word	0x46000134
/* 000199 0x80BFD2BC */ .word	0x45000168
/* 000200 0x80BFD2C0 */ .word	0x4600017C
/* 000201 0x80BFD2C4 */ .word	0x4500025C
/* 000202 0x80BFD2C8 */ .word	0x46000274
/* 000203 0x80BFD2CC */ .word	0x82000010
/* 000204 0x80BFD2D0 */ .word	0x82000014
/* 000205 0x80BFD2D4 */ .word	0x82000018
/* 000206 0x80BFD2D8 */ .word	0x8200001C
glabel enScopecoinOverlayInfoOffset
/* 000207 0x80BFD2DC */ .word	0x00000040
