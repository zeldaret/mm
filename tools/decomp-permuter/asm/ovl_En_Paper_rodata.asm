.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enPaperOverlayInfo
/* 000556 0x80C1FC80 */ .word	0x00000870
/* 000557 0x80C1FC84 */ .word	0x00000030
/* 000558 0x80C1FC88 */ .word	0x00000010
/* 000559 0x80C1FC8C */ .word	0x00000000
/* 000560 0x80C1FC90 */ .word	0x00000015
glabel enPaperOverlayRelocations
/* 000561 0x80C1FC94 */ .word	0x45000028
/* 000562 0x80C1FC98 */ .word	0x46000030
/* 000563 0x80C1FC9C */ .word	0x44000070
/* 000564 0x80C1FCA0 */ .word	0x4500009C
/* 000565 0x80C1FCA4 */ .word	0x460000A0
/* 000566 0x80C1FCA8 */ .word	0x440000E0
/* 000567 0x80C1FCAC */ .word	0x440000F4
/* 000568 0x80C1FCB0 */ .word	0x45000118
/* 000569 0x80C1FCB4 */ .word	0x4600011C
/* 000570 0x80C1FCB8 */ .word	0x4400015C
/* 000571 0x80C1FCBC */ .word	0x450001D0
/* 000572 0x80C1FCC0 */ .word	0x460001E0
/* 000573 0x80C1FCC4 */ .word	0x450002EC
/* 000574 0x80C1FCC8 */ .word	0x460002F0
/* 000575 0x80C1FCCC */ .word	0x45000388
/* 000576 0x80C1FCD0 */ .word	0x46000390
/* 000577 0x80C1FCD4 */ .word	0x440005C4
/* 000578 0x80C1FCD8 */ .word	0x82000010
/* 000579 0x80C1FCDC */ .word	0x82000014
/* 000580 0x80C1FCE0 */ .word	0x82000018
/* 000581 0x80C1FCE4 */ .word	0x8200001C
/* 000582 0x80C1FCE8 */ .word	0x00000000
glabel enPaperOverlayInfoOffset
/* 000583 0x80C1FCEC */ .word	0x00000070
