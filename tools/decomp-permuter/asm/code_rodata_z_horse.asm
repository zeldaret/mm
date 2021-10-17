.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DD7E0
/* 319304 0x801DD7E0 */ .word	0x43808000
glabel D_801DD7E4
/* 319305 0x801DD7E4 */ .word	0xC4A0A000
glabel D_801DD7E8
/* 319306 0x801DD7E8 */ .word	0xC4204000
glabel D_801DD7EC
/* 319307 0x801DD7EC */ .word	0xC4942000
