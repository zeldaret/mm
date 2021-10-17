.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel demoMoonendOverlayInfo
/* 000420 0x80C180A0 */ .word	0x00000660
/* 000421 0x80C180A4 */ .word	0x00000020
/* 000422 0x80C180A8 */ .word	0x00000010
/* 000423 0x80C180AC */ .word	0x00000000
/* 000424 0x80C180B0 */ .word	0x00000018
glabel demoMoonendOverlayRelocations
/* 000425 0x80C180B4 */ .word	0x45000028
/* 000426 0x80C180B8 */ .word	0x4600002C
/* 000427 0x80C180BC */ .word	0x4500005C
/* 000428 0x80C180C0 */ .word	0x46000064
/* 000429 0x80C180C4 */ .word	0x450000C4
/* 000430 0x80C180C8 */ .word	0x460000CC
/* 000431 0x80C180CC */ .word	0x450000E0
/* 000432 0x80C180D0 */ .word	0x460000E4
/* 000433 0x80C180D4 */ .word	0x450001E0
/* 000434 0x80C180D8 */ .word	0x460001F8
/* 000435 0x80C180DC */ .word	0x450002E4
/* 000436 0x80C180E0 */ .word	0x460002E8
/* 000437 0x80C180E4 */ .word	0x450002D8
/* 000438 0x80C180E8 */ .word	0x4600030C
/* 000439 0x80C180EC */ .word	0x45000324
/* 000440 0x80C180F0 */ .word	0x46000328
/* 000441 0x80C180F4 */ .word	0x45000588
/* 000442 0x80C180F8 */ .word	0x46000590
/* 000443 0x80C180FC */ .word	0x45000580
/* 000444 0x80C18100 */ .word	0x46000584
/* 000445 0x80C18104 */ .word	0x82000010
/* 000446 0x80C18108 */ .word	0x82000014
/* 000447 0x80C1810C */ .word	0x82000018
/* 000448 0x80C18110 */ .word	0x8200001C
/* 000449 0x80C18114 */ .word	0x00000000
/* 000450 0x80C18118 */ .word	0x00000000
glabel demoMoonendOverlayInfoOffset
/* 000451 0x80C1811C */ .word	0x00000080
