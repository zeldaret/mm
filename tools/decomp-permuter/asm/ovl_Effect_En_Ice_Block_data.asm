.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_80A23020
/* 000184 0x80A23020 */ .word	0x00000025
/* 000185 0x80A23024 */ .word	func_80A22DB8
/* 000186 0x80A23028 */ .word	0x00000000
/* 000187 0x80A2302C */ .word	0x00000000
glabel D_80A23030
/* 000188 0x80A23030 */ .word	0x477FFF00
glabel D_80A23034
/* 000189 0x80A23034 */ .word	0x3DCCCCCD
glabel D_80A23038
/* 000190 0x80A23038 */ .word	0x3C23D70A
/* 000191 0x80A2303C */ .word	0x00000000
glabel effectEnIceBlockOverlayInfo
/* 000192 0x80A23040 */ .word	0x000002E0
/* 000193 0x80A23044 */ .word	0x00000010
/* 000194 0x80A23048 */ .word	0x00000010
/* 000195 0x80A2304C */ .word	0x00000000
/* 000196 0x80A23050 */ .word	0x0000000E
glabel effectEnIceBlockOverlayRelocations
/* 000197 0x80A23054 */ .word	0x450000D4
/* 000198 0x80A23058 */ .word	0x460000D8
/* 000199 0x80A2305C */ .word	0x450000F8
/* 000200 0x80A23060 */ .word	0x46000108
/* 000201 0x80A23064 */ .word	0x450000FC
/* 000202 0x80A23068 */ .word	0x4600010C
/* 000203 0x80A2306C */ .word	0x44000134
/* 000204 0x80A23070 */ .word	0x4400017C
/* 000205 0x80A23074 */ .word	0x45000190
/* 000206 0x80A23078 */ .word	0x46000194
/* 000207 0x80A2307C */ .word	0x4500019C
/* 000208 0x80A23080 */ .word	0x460001A0
/* 000209 0x80A23084 */ .word	0x440002C8
/* 000210 0x80A23088 */ .word	0x82000004
glabel effectEnIceBlockOverlayInfoOffset
/* 000211 0x80A2308C */ .word	0x00000050
