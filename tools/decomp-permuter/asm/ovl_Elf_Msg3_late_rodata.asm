.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_80A2D200
/* 000316 0x80A2D200 */ .word	0x3ECCCCCD
glabel D_80A2D204
/* 000317 0x80A2D204 */ .word	0x3D23D70A
glabel D_80A2D208
/* 000318 0x80A2D208 */ .word	0x3ECCCCCD
glabel D_80A2D20C
/* 000319 0x80A2D20C */ .word	0x3D23D70A
glabel elfMsg3OverlayInfo
/* 000320 0x80A2D210 */ .word	0x000004B0
/* 000321 0x80A2D214 */ .word	0x00000030
/* 000322 0x80A2D218 */ .word	0x00000020
/* 000323 0x80A2D21C */ .word	0x00000000
/* 000324 0x80A2D220 */ .word	0x00000013
glabel elfMsg3OverlayRelocations
/* 000325 0x80A2D224 */ .word	0x44000154
/* 000326 0x80A2D228 */ .word	0x45000164
/* 000327 0x80A2D22C */ .word	0x4600016C
/* 000328 0x80A2D230 */ .word	0x45000190
/* 000329 0x80A2D234 */ .word	0x46000194
/* 000330 0x80A2D238 */ .word	0x450001B8
/* 000331 0x80A2D23C */ .word	0x460001BC
/* 000332 0x80A2D240 */ .word	0x450001C4
/* 000333 0x80A2D244 */ .word	0x460001D4
/* 000334 0x80A2D248 */ .word	0x450001F0
/* 000335 0x80A2D24C */ .word	0x460001F4
/* 000336 0x80A2D250 */ .word	0x45000178
/* 000337 0x80A2D254 */ .word	0x46000208
/* 000338 0x80A2D258 */ .word	0x44000204
/* 000339 0x80A2D25C */ .word	0x44000324
/* 000340 0x80A2D260 */ .word	0x44000408
/* 000341 0x80A2D264 */ .word	0x82000010
/* 000342 0x80A2D268 */ .word	0x82000014
/* 000343 0x80A2D26C */ .word	0x82000018
/* 000344 0x80A2D270 */ .word	0x00000000
/* 000345 0x80A2D274 */ .word	0x00000000
/* 000346 0x80A2D278 */ .word	0x00000000
glabel elfMsg3OverlayInfoOffset
/* 000347 0x80A2D27C */ .word	0x00000070
