.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objBlockstopOverlayInfo
/* 000128 0x809468A0 */ .word	0x000001E0
/* 000129 0x809468A4 */ .word	0x00000020
/* 000130 0x809468A8 */ .word	0x00000000
/* 000131 0x809468AC */ .word	0x00000000
/* 000132 0x809468B0 */ .word	0x00000006
glabel objBlockstopOverlayRelocations
/* 000133 0x809468B4 */ .word	0x45000034
/* 000134 0x809468B8 */ .word	0x46000038
/* 000135 0x809468BC */ .word	0x450000F8
/* 000136 0x809468C0 */ .word	0x460000FC
/* 000137 0x809468C4 */ .word	0x82000010
/* 000138 0x809468C8 */ .word	0x82000018
glabel objBlockstopOverlayInfoOffset
/* 000139 0x809468CC */ .word	0x00000030
