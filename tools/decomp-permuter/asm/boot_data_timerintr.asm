.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel __osTimerList
/* 024516 0x80097F70 */ .word	D_8009E590
/* 024517 0x80097F74 */ .word	0x00000000
/* 024518 0x80097F78 */ .word	0x00000000
/* 024519 0x80097F7C */ .word	0x00000000
