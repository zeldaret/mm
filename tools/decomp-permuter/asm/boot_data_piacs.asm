.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel __osPiAccessQueueEnabled
/* 024464 0x80097EA0 */ .word	0x00000000
/* 024465 0x80097EA4 */ .word	0x00000000
/* 024466 0x80097EA8 */ .word	0x00000000
/* 024467 0x80097EAC */ .word	0x00000000
