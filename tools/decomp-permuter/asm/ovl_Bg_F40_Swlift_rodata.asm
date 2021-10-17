.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgF40SwliftOverlayInfo
/* 000256 0x8096F560 */ .word	0x000003B0
/* 000257 0x8096F564 */ .word	0x00000040
/* 000258 0x8096F568 */ .word	0x00000010
/* 000259 0x8096F56C */ .word	0x00000010
/* 000260 0x8096F570 */ .word	0x00000014
glabel bgF40SwliftOverlayRelocations
/* 000261 0x8096F574 */ .word	0x45000014
/* 000262 0x8096F578 */ .word	0x46000018
/* 000263 0x8096F57C */ .word	0x45000064
/* 000264 0x8096F580 */ .word	0x46000080
/* 000265 0x8096F584 */ .word	0x45000088
/* 000266 0x8096F588 */ .word	0x46000098
/* 000267 0x8096F58C */ .word	0x45000124
/* 000268 0x8096F590 */ .word	0x46000128
/* 000269 0x8096F594 */ .word	0x45000178
/* 000270 0x8096F598 */ .word	0x4600017C
/* 000271 0x8096F59C */ .word	0x45000190
/* 000272 0x8096F5A0 */ .word	0x46000198
/* 000273 0x8096F5A4 */ .word	0x45000314
/* 000274 0x8096F5A8 */ .word	0x4600031C
/* 000275 0x8096F5AC */ .word	0x45000330
/* 000276 0x8096F5B0 */ .word	0x46000340
/* 000277 0x8096F5B4 */ .word	0x82000020
/* 000278 0x8096F5B8 */ .word	0x82000024
/* 000279 0x8096F5BC */ .word	0x82000028
/* 000280 0x8096F5C0 */ .word	0x8200002C
/* 000281 0x8096F5C4 */ .word	0x00000000
/* 000282 0x8096F5C8 */ .word	0x00000000
glabel bgF40SwliftOverlayInfoOffset
/* 000283 0x8096F5CC */ .word	0x00000070
