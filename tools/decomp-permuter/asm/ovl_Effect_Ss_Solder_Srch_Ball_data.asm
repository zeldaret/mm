.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_8097DC40
/* 000252 0x8097DC40 */ .word	0x00000018
/* 000253 0x8097DC44 */ .word	func_8097D850
/* 000254 0x8097DC48 */ .word	0x00000000
/* 000255 0x8097DC4C */ .word	0x00000000
glabel D_8097DC50
/* 000256 0x8097DC50 */ .word	0x3C8EFA35
/* 000257 0x8097DC54 */ .word	0x00000000
/* 000258 0x8097DC58 */ .word	0x00000000
/* 000259 0x8097DC5C */ .word	0x00000000
glabel effectSsSolderSrchBallOverlayInfo
/* 000260 0x8097DC60 */ .word	0x000003F0
/* 000261 0x8097DC64 */ .word	0x00000010
/* 000262 0x8097DC68 */ .word	0x00000010
/* 000263 0x8097DC6C */ .word	0x00000000
/* 000264 0x8097DC70 */ .word	0x00000007
glabel effectSsSolderSrchBallOverlayRelocations
/* 000265 0x8097DC74 */ .word	0x4500000C
/* 000266 0x8097DC78 */ .word	0x46000010
/* 000267 0x8097DC7C */ .word	0x4500001C
/* 000268 0x8097DC80 */ .word	0x46000020
/* 000269 0x8097DC84 */ .word	0x4500021C
/* 000270 0x8097DC88 */ .word	0x46000220
/* 000271 0x8097DC8C */ .word	0x82000004
/* 000272 0x8097DC90 */ .word	0x00000000
/* 000273 0x8097DC94 */ .word	0x00000000
/* 000274 0x8097DC98 */ .word	0x00000000
glabel effectSsSolderSrchBallOverlayInfoOffset
/* 000275 0x8097DC9C */ .word	0x00000040
