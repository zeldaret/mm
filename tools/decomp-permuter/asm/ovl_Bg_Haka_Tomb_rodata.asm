.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgHakaTombOverlayInfo
/* 000204 0x80BD68B0 */ .word	0x00000300
/* 000205 0x80BD68B4 */ .word	0x00000030
/* 000206 0x80BD68B8 */ .word	0x00000000
/* 000207 0x80BD68BC */ .word	0x00000000
/* 000208 0x80BD68C0 */ .word	0x00000012
glabel bgHakaTombOverlayRelocations
/* 000209 0x80BD68C4 */ .word	0x45000014
/* 000210 0x80BD68C8 */ .word	0x46000018
/* 000211 0x80BD68CC */ .word	0x44000054
/* 000212 0x80BD68D0 */ .word	0x450000A4
/* 000213 0x80BD68D4 */ .word	0x460000A8
/* 000214 0x80BD68D8 */ .word	0x44000164
/* 000215 0x80BD68DC */ .word	0x440001A0
/* 000216 0x80BD68E0 */ .word	0x450001D4
/* 000217 0x80BD68E4 */ .word	0x460001D8
/* 000218 0x80BD68E8 */ .word	0x44000210
/* 000219 0x80BD68EC */ .word	0x45000228
/* 000220 0x80BD68F0 */ .word	0x4600022C
/* 000221 0x80BD68F4 */ .word	0x45000290
/* 000222 0x80BD68F8 */ .word	0x46000294
/* 000223 0x80BD68FC */ .word	0x82000010
/* 000224 0x80BD6900 */ .word	0x82000014
/* 000225 0x80BD6904 */ .word	0x82000018
/* 000226 0x80BD6908 */ .word	0x8200001C
glabel bgHakaTombOverlayInfoOffset
/* 000227 0x80BD690C */ .word	0x00000060
