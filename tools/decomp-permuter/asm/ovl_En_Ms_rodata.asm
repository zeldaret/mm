.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enMsOverlayInfo
/* 000368 0x80952BE0 */ .word	0x00000560
/* 000369 0x80952BE4 */ .word	0x00000060
/* 000370 0x80952BE8 */ .word	0x00000000
/* 000371 0x80952BEC */ .word	0x00000000
/* 000372 0x80952BF0 */ .word	0x00000016
glabel enMsOverlayRelocations
/* 000373 0x80952BF4 */ .word	0x45000014
/* 000374 0x80952BF8 */ .word	0x46000018
/* 000375 0x80952BFC */ .word	0x45000068
/* 000376 0x80952C00 */ .word	0x46000070
/* 000377 0x80952C04 */ .word	0x450000B4
/* 000378 0x80952C08 */ .word	0x460000BC
/* 000379 0x80952C0C */ .word	0x45000174
/* 000380 0x80952C10 */ .word	0x46000178
/* 000381 0x80952C14 */ .word	0x4500021C
/* 000382 0x80952C18 */ .word	0x46000224
/* 000383 0x80952C1C */ .word	0x45000268
/* 000384 0x80952C20 */ .word	0x4600026C
/* 000385 0x80952C24 */ .word	0x45000354
/* 000386 0x80952C28 */ .word	0x46000358
/* 000387 0x80952C2C */ .word	0x450003C8
/* 000388 0x80952C30 */ .word	0x460003CC
/* 000389 0x80952C34 */ .word	0x45000430
/* 000390 0x80952C38 */ .word	0x46000434
/* 000391 0x80952C3C */ .word	0x82000010
/* 000392 0x80952C40 */ .word	0x82000014
/* 000393 0x80952C44 */ .word	0x82000018
/* 000394 0x80952C48 */ .word	0x8200001C
glabel enMsOverlayInfoOffset
/* 000395 0x80952C4C */ .word	0x00000070
