.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DF0A0
/* 320888 0x801DF0A0 */ .word	0x3DCCCCCD
/* 320889 0x801DF0A4 */ .word	0x00000000
/* 320890 0x801DF0A8 */ .word	0x00000000
/* 320891 0x801DF0AC */ .word	0x00000000
