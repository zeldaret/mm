.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enHitTagOverlayInfo
/* 000124 0x80BE2220 */ .word	0x000001A0
/* 000125 0x80BE2224 */ .word	0x00000050
/* 000126 0x80BE2228 */ .word	0x00000000
/* 000127 0x80BE222C */ .word	0x00000000
/* 000128 0x80BE2230 */ .word	0x00000007
glabel enHitTagOverlayRelocations
/* 000129 0x80BE2234 */ .word	0x45000020
/* 000130 0x80BE2238 */ .word	0x46000024
/* 000131 0x80BE223C */ .word	0x45000030
/* 000132 0x80BE2240 */ .word	0x46000034
/* 000133 0x80BE2244 */ .word	0x82000010
/* 000134 0x80BE2248 */ .word	0x82000014
/* 000135 0x80BE224C */ .word	0x82000018
/* 000136 0x80BE2250 */ .word	0x00000000
/* 000137 0x80BE2254 */ .word	0x00000000
/* 000138 0x80BE2258 */ .word	0x00000000
glabel enHitTagOverlayInfoOffset
/* 000139 0x80BE225C */ .word	0x00000040
