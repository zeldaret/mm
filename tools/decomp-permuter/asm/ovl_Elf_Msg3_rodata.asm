.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

/* 000312 0x80A2D1F0 */ .word	0xB6A6C5DD
/* 000313 0x80A2D1F4 */ .word	0xA4EC0000
/* 000314 0x80A2D1F8 */ .word	0xB6A6C5DD
/* 000315 0x80A2D1FC */ .word	0xA4EC0000
