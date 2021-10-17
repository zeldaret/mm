.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgHakuginElvpoleOverlayInfo
/* 000272 0x80ABDC70 */ .word	0x00000420
/* 000273 0x80ABDC74 */ .word	0x00000020
/* 000274 0x80ABDC78 */ .word	0x00000000
/* 000275 0x80ABDC7C */ .word	0x00000000
/* 000276 0x80ABDC80 */ .word	0x00000006
glabel bgHakuginElvpoleOverlayRelocations
/* 000277 0x80ABDC84 */ .word	0x45000028
/* 000278 0x80ABDC88 */ .word	0x4600002C
/* 000279 0x80ABDC8C */ .word	0x82000010
/* 000280 0x80ABDC90 */ .word	0x82000014
/* 000281 0x80ABDC94 */ .word	0x82000018
/* 000282 0x80ABDC98 */ .word	0x8200001C
glabel bgHakuginElvpoleOverlayInfoOffset
/* 000283 0x80ABDC9C */ .word	0x00000030
