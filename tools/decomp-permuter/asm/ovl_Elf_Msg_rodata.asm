.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

/* 000316 0x8092E480 */ .word	0xB6A6C5DD
/* 000317 0x8092E484 */ .word	0xA4EC0000
/* 000318 0x8092E488 */ .word	0xB6A6C5DD
/* 000319 0x8092E48C */ .word	0xA4EC0000
