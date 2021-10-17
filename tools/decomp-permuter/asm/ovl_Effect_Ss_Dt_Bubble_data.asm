.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_8097B1E0
/* 000288 0x8097B1E0 */ .word	0xFFFF64FF
/* 000289 0x8097B1E4 */ .word	0x96FFFFFF
/* 000290 0x8097B1E8 */ .word	0x64FFFFFF
/* 000291 0x8097B1EC */ .word	0xFFFFFFFF
glabel D_8097B1F0
/* 000292 0x8097B1F0 */ .word	0xAA0000FF
/* 000293 0x8097B1F4 */ .word	0x006400FF
/* 000294 0x8097B1F8 */ .word	0x0000FFFF
/* 000295 0x8097B1FC */ .word	0x96969600
glabel D_8097B200
/* 000296 0x8097B200 */ .word	0x0000000E
/* 000297 0x8097B204 */ .word	func_8097AD60
/* 000298 0x8097B208 */ .word	0x00000000
/* 000299 0x8097B20C */ .word	0x00000000
glabel D_8097B210
/* 000300 0x8097B210 */ .word	0x3B83126F
/* 000301 0x8097B214 */ .word	0x00000000
/* 000302 0x8097B218 */ .word	0x00000000
/* 000303 0x8097B21C */ .word	0x00000000
glabel effectSsDtBubbleOverlayInfo
/* 000304 0x8097B220 */ .word	0x00000480
/* 000305 0x8097B224 */ .word	0x00000030
/* 000306 0x8097B228 */ .word	0x00000010
/* 000307 0x8097B22C */ .word	0x00000000
/* 000308 0x8097B230 */ .word	0x0000000B
glabel effectSsDtBubbleOverlayRelocations
/* 000309 0x8097B234 */ .word	0x450000B8
/* 000310 0x8097B238 */ .word	0x460000BC
/* 000311 0x8097B23C */ .word	0x450000CC
/* 000312 0x8097B240 */ .word	0x460000D0
/* 000313 0x8097B244 */ .word	0x450001AC
/* 000314 0x8097B248 */ .word	0x460001BC
/* 000315 0x8097B24C */ .word	0x450001B0
/* 000316 0x8097B250 */ .word	0x460001C0
/* 000317 0x8097B254 */ .word	0x45000210
/* 000318 0x8097B258 */ .word	0x46000214
/* 000319 0x8097B25C */ .word	0x82000024
/* 000320 0x8097B260 */ .word	0x00000000
/* 000321 0x8097B264 */ .word	0x00000000
/* 000322 0x8097B268 */ .word	0x00000000
glabel effectSsDtBubbleOverlayInfoOffset
/* 000323 0x8097B26C */ .word	0x00000050
