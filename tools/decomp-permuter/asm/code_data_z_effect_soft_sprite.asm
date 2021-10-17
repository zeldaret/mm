.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel EffectSS2Info
/* 270904 0x801AE3A0 */ .word	0x00000000
/* 270905 0x801AE3A4 */ .word	0x00000000
/* 270906 0x801AE3A8 */ .word	0x00000000
/* 270907 0x801AE3AC */ .word	0x00000000
