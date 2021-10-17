.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel jtbl_D_801DC0E0
/* 317832 0x801DC0E0 */ .word	L800AF9C4
/* 317833 0x801DC0E4 */ .word	L800AFA08
/* 317834 0x801DC0E8 */ .word	L800AFA08
/* 317835 0x801DC0EC */ .word	L800AFA4C
/* 317836 0x801DC0F0 */ .word	L800AFA90
/* 317837 0x801DC0F4 */ .word	0x00000000
/* 317838 0x801DC0F8 */ .word	0x00000000
/* 317839 0x801DC0FC */ .word	0x00000000
