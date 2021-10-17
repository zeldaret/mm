.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_80099270
/* 025732 0x80099270 */ .word	0x00141818
/* 025733 0x80099274 */ .word	0x1C1C1C1C
/* 025734 0x80099278 */ .word	0x20202020
/* 025735 0x8009927C */ .word	0x20202020
/* 025736 0x80099280 */ .word	0x00040808
/* 025737 0x80099284 */ .word	0x0C0C0C0C
/* 025738 0x80099288 */ .word	0x10101010
/* 025739 0x8009928C */ .word	0x10101010
glabel __osIntTable
/* 025740 0x80099290 */ .word	func_80088FE0
/* 025741 0x80099294 */ .word	func_80088FA8
/* 025742 0x80099298 */ .word	func_80088F88
/* 025743 0x8009929C */ .word	func_80088DC4
/* 025744 0x800992A0 */ .word	func_80088D80
/* 025745 0x800992A4 */ .word	func_80088F2C
/* 025746 0x800992A8 */ .word	func_80088D48
/* 025747 0x800992AC */ .word	func_80088D54
/* 025748 0x800992B0 */ .word	func_80088D60
/* 025749 0x800992B4 */ .word	0x00000000
/* 025750 0x800992B8 */ .word	0x00000000
/* 025751 0x800992BC */ .word	0x00000000
