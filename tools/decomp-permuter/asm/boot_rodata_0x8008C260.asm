.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel jtbl_D_800992D0
/* 025756 0x800992D0 */ .word	L8008C5DC
/* 025757 0x800992D4 */ .word	L8008C4F4
/* 025758 0x800992D8 */ .word	L8008C528
/* 025759 0x800992DC */ .word	L8008C5F8
/* 025760 0x800992E0 */ .word	L8008C5F8
/* 025761 0x800992E4 */ .word	L8008C55C
/* 025762 0x800992E8 */ .word	L8008C59C
/* 025763 0x800992EC */ .word	0x00000000
