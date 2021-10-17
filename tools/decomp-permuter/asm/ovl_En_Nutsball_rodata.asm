.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enNutsballOverlayInfo
/* 000380 0x80986230 */ .word	0x00000590
/* 000381 0x80986234 */ .word	0x00000050
/* 000382 0x80986238 */ .word	0x00000010
/* 000383 0x8098623C */ .word	0x00000000
/* 000384 0x80986240 */ .word	0x0000000A
glabel enNutsballOverlayRelocations
/* 000385 0x80986244 */ .word	0x4500002C
/* 000386 0x80986248 */ .word	0x46000030
/* 000387 0x8098624C */ .word	0x440000B4
/* 000388 0x80986250 */ .word	0x44000240
/* 000389 0x80986254 */ .word	0x45000410
/* 000390 0x80986258 */ .word	0x46000414
/* 000391 0x8098625C */ .word	0x82000010
/* 000392 0x80986260 */ .word	0x82000014
/* 000393 0x80986264 */ .word	0x82000018
/* 000394 0x80986268 */ .word	0x8200001C
glabel enNutsballOverlayInfoOffset
/* 000395 0x8098626C */ .word	0x00000040
