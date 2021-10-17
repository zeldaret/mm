.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_801D1540
/* 306848 0x801D1540 */ .word	D_801FBAE0
/* 306849 0x801D1544 */ .word	0x00000006
/* 306850 0x801D1548 */ .word	0x003F0000
/* 306851 0x801D154C */ .word	D_801FBAE8
/* 306852 0x801D1550 */ .word	0x00000008
/* 306853 0x801D1554 */ .word	0xFC210000
/* 306854 0x801D1558 */ .word	D_801FBAF0
/* 306855 0x801D155C */ .word	0x0000000A
/* 306856 0x801D1560 */ .word	0x07C10000
/* 306857 0x801D1564 */ .word	lastRenderFrameDuration
/* 306858 0x801D1568 */ .word	0x0000000C
/* 306859 0x801D156C */ .word	0xF83F0000
