.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

/* 004584 0x80A8FF10 */ .word	0x2E2E2F7A
/* 004585 0x80A8FF14 */ .word	0x5F656E5F
/* 004586 0x80A8FF18 */ .word	0x7472742E
/* 004587 0x80A8FF1C */ .word	0x63000000
/* 004588 0x80A8FF20 */ .word	0x2E2E2F7A
/* 004589 0x80A8FF24 */ .word	0x5F656E5F
/* 004590 0x80A8FF28 */ .word	0x7472742E
/* 004591 0x80A8FF2C */ .word	0x63000000
