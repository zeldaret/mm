.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgLadderOverlayInfo
/* 000284 0x80A4DE60 */ .word	0x00000430
/* 000285 0x80A4DE64 */ .word	0x00000040
/* 000286 0x80A4DE68 */ .word	0x00000000
/* 000287 0x80A4DE6C */ .word	0x00000000
/* 000288 0x80A4DE70 */ .word	0x00000014
glabel bgLadderOverlayRelocations
/* 000289 0x80A4DE74 */ .word	0x45000018
/* 000290 0x80A4DE78 */ .word	0x4600001C
/* 000291 0x80A4DE7C */ .word	0x4500010C
/* 000292 0x80A4DE80 */ .word	0x46000114
/* 000293 0x80A4DE84 */ .word	0x45000140
/* 000294 0x80A4DE88 */ .word	0x46000144
/* 000295 0x80A4DE8C */ .word	0x450001CC
/* 000296 0x80A4DE90 */ .word	0x460001D0
/* 000297 0x80A4DE94 */ .word	0x45000214
/* 000298 0x80A4DE98 */ .word	0x46000218
/* 000299 0x80A4DE9C */ .word	0x4500022C
/* 000300 0x80A4DEA0 */ .word	0x46000230
/* 000301 0x80A4DEA4 */ .word	0x450002B4
/* 000302 0x80A4DEA8 */ .word	0x460002BC
/* 000303 0x80A4DEAC */ .word	0x450003E0
/* 000304 0x80A4DEB0 */ .word	0x460003F8
/* 000305 0x80A4DEB4 */ .word	0x82000010
/* 000306 0x80A4DEB8 */ .word	0x82000014
/* 000307 0x80A4DEBC */ .word	0x82000018
/* 000308 0x80A4DEC0 */ .word	0x8200001C
/* 000309 0x80A4DEC4 */ .word	0x00000000
/* 000310 0x80A4DEC8 */ .word	0x00000000
glabel bgLadderOverlayInfoOffset
/* 000311 0x80A4DECC */ .word	0x00000070
