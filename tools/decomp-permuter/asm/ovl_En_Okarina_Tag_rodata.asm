.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enOkarinaTagOverlayInfo
/* 000264 0x8093E840 */ .word	0x000003F0
/* 000265 0x8093E844 */ .word	0x00000020
/* 000266 0x8093E848 */ .word	0x00000010
/* 000267 0x8093E84C */ .word	0x00000000
/* 000268 0x8093E850 */ .word	0x0000000F
glabel enOkarinaTagOverlayRelocations
/* 000269 0x8093E854 */ .word	0x450000AC
/* 000270 0x8093E858 */ .word	0x460000C4
/* 000271 0x8093E85C */ .word	0x450001B0
/* 000272 0x8093E860 */ .word	0x460001B4
/* 000273 0x8093E864 */ .word	0x4500021C
/* 000274 0x8093E868 */ .word	0x46000228
/* 000275 0x8093E86C */ .word	0x45000234
/* 000276 0x8093E870 */ .word	0x46000248
/* 000277 0x8093E874 */ .word	0x45000290
/* 000278 0x8093E878 */ .word	0x4600029C
/* 000279 0x8093E87C */ .word	0x450003A8
/* 000280 0x8093E880 */ .word	0x460003AC
/* 000281 0x8093E884 */ .word	0x82000010
/* 000282 0x8093E888 */ .word	0x82000014
/* 000283 0x8093E88C */ .word	0x82000018
/* 000284 0x8093E890 */ .word	0x00000000
/* 000285 0x8093E894 */ .word	0x00000000
/* 000286 0x8093E898 */ .word	0x00000000
glabel enOkarinaTagOverlayInfoOffset
/* 000287 0x8093E89C */ .word	0x00000060
