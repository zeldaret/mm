.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel irqmgrThreadName
/* 024656 0x800981A0 */ .word	0x6972716D
/* 024657 0x800981A4 */ .word	0x67720000
glabel mainThreadName
/* 024658 0x800981A8 */ .word	0x6D61696E
/* 024659 0x800981AC */ .word	0x00000000
glabel D_800981B0
/* 024660 0x800981B0 */ .word	0x3F553F7D
/* 024661 0x800981B4 */ .word	0x00000000
/* 024662 0x800981B8 */ .word	0x00000000
/* 024663 0x800981BC */ .word	0x00000000
