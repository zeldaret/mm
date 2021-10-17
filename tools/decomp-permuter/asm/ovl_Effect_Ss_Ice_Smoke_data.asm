.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_8099F9E0
/* 000172 0x8099F9E0 */ .word	0x00000024
/* 000173 0x8099F9E4 */ .word	func_8099F730
/* 000174 0x8099F9E8 */ .word	0x00000000
/* 000175 0x8099F9EC */ .word	0x00000000
glabel D_8099F9F0
/* 000176 0x8099F9F0 */ .word	0x38D1B717
/* 000177 0x8099F9F4 */ .word	0x00000000
/* 000178 0x8099F9F8 */ .word	0x00000000
/* 000179 0x8099F9FC */ .word	0x00000000
glabel effectSsIceSmokeOverlayInfo
/* 000180 0x8099FA00 */ .word	0x000002B0
/* 000181 0x8099FA04 */ .word	0x00000010
/* 000182 0x8099FA08 */ .word	0x00000010
/* 000183 0x8099FA0C */ .word	0x00000000
/* 000184 0x8099FA10 */ .word	0x00000007
glabel effectSsIceSmokeOverlayRelocations
/* 000185 0x8099FA14 */ .word	0x4500004C
/* 000186 0x8099FA18 */ .word	0x46000058
/* 000187 0x8099FA1C */ .word	0x45000070
/* 000188 0x8099FA20 */ .word	0x46000074
/* 000189 0x8099FA24 */ .word	0x450001CC
/* 000190 0x8099FA28 */ .word	0x460001D0
/* 000191 0x8099FA2C */ .word	0x82000004
/* 000192 0x8099FA30 */ .word	0x00000000
/* 000193 0x8099FA34 */ .word	0x00000000
/* 000194 0x8099FA38 */ .word	0x00000000
glabel effectSsIceSmokeOverlayInfoOffset
/* 000195 0x8099FA3C */ .word	0x00000040
