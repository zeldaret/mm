.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

/* 000352 0x80AFD900 */ .word	0xB6A6C5DD
/* 000353 0x80AFD904 */ .word	0xA4EC0000
/* 000354 0x80AFD908 */ .word	0xB6A6C5DD
/* 000355 0x80AFD90C */ .word	0xA4EC0000
