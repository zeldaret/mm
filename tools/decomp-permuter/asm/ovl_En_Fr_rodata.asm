.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enFrOverlayInfo
/* 000080 0x808FC690 */ .word	0x00000120
/* 000081 0x808FC694 */ .word	0x00000020
/* 000082 0x808FC698 */ .word	0x00000000
/* 000083 0x808FC69C */ .word	0x00000000
/* 000084 0x808FC6A0 */ .word	0x00000003
glabel enFrOverlayRelocations
/* 000085 0x808FC6A4 */ .word	0x82000010
/* 000086 0x808FC6A8 */ .word	0x82000014
/* 000087 0x808FC6AC */ .word	0x82000018
/* 000088 0x808FC6B0 */ .word	0x00000000
/* 000089 0x808FC6B4 */ .word	0x00000000
/* 000090 0x808FC6B8 */ .word	0x00000000
glabel enFrOverlayInfoOffset
/* 000091 0x808FC6BC */ .word	0x00000030
