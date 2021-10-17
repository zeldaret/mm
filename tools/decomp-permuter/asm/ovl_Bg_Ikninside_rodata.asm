.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgIkninsideOverlayInfo
/* 000372 0x80C076E0 */ .word	0x00000570
/* 000373 0x80C076E4 */ .word	0x00000060
/* 000374 0x80C076E8 */ .word	0x00000000
/* 000375 0x80C076EC */ .word	0x00000000
/* 000376 0x80C076F0 */ .word	0x00000012
glabel bgIkninsideOverlayRelocations
/* 000377 0x80C076F4 */ .word	0x45000028
/* 000378 0x80C076F8 */ .word	0x4600002C
/* 000379 0x80C076FC */ .word	0x4500006C
/* 000380 0x80C07700 */ .word	0x46000070
/* 000381 0x80C07704 */ .word	0x4500013C
/* 000382 0x80C07708 */ .word	0x46000144
/* 000383 0x80C0770C */ .word	0x45000194
/* 000384 0x80C07710 */ .word	0x46000198
/* 000385 0x80C07714 */ .word	0x45000240
/* 000386 0x80C07718 */ .word	0x4600026C
/* 000387 0x80C0771C */ .word	0x4500025C
/* 000388 0x80C07720 */ .word	0x46000264
/* 000389 0x80C07724 */ .word	0x450003D8
/* 000390 0x80C07728 */ .word	0x460003DC
/* 000391 0x80C0772C */ .word	0x82000010
/* 000392 0x80C07730 */ .word	0x82000014
/* 000393 0x80C07734 */ .word	0x82000018
/* 000394 0x80C07738 */ .word	0x8200001C
glabel bgIkninsideOverlayInfoOffset
/* 000395 0x80C0773C */ .word	0x00000060
