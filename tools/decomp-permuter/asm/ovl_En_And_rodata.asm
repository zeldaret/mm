.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enAndOverlayInfo
/* 000424 0x80C19230 */ .word	0x000005D0
/* 000425 0x80C19234 */ .word	0x000000D0
/* 000426 0x80C19238 */ .word	0x00000000
/* 000427 0x80C1923C */ .word	0x00000000
/* 000428 0x80C19240 */ .word	0x00000015
glabel enAndOverlayRelocations
/* 000429 0x80C19244 */ .word	0x45000020
/* 000430 0x80C19248 */ .word	0x4600002C
/* 000431 0x80C1924C */ .word	0x450000D4
/* 000432 0x80C19250 */ .word	0x460000D8
/* 000433 0x80C19254 */ .word	0x44000194
/* 000434 0x80C19258 */ .word	0x440001E8
/* 000435 0x80C1925C */ .word	0x4400021C
/* 000436 0x80C19260 */ .word	0x440002A0
/* 000437 0x80C19264 */ .word	0x450002C4
/* 000438 0x80C19268 */ .word	0x460002C8
/* 000439 0x80C1926C */ .word	0x44000328
/* 000440 0x80C19270 */ .word	0x45000538
/* 000441 0x80C19274 */ .word	0x46000548
/* 000442 0x80C19278 */ .word	0x4500056C
/* 000443 0x80C1927C */ .word	0x4600057C
/* 000444 0x80C19280 */ .word	0x4500058C
/* 000445 0x80C19284 */ .word	0x46000590
/* 000446 0x80C19288 */ .word	0x82000010
/* 000447 0x80C1928C */ .word	0x82000014
/* 000448 0x80C19290 */ .word	0x82000018
/* 000449 0x80C19294 */ .word	0x8200001C
/* 000450 0x80C19298 */ .word	0x00000000
glabel enAndOverlayInfoOffset
/* 000451 0x80C1929C */ .word	0x00000070
