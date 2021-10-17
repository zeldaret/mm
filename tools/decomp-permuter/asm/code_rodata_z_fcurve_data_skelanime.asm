.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DD7C0
/* 319296 0x801DD7C0 */ .word	0x43360B61
/* 319297 0x801DD7C4 */ .word	0x00000000
/* 319298 0x801DD7C8 */ .word	0x00000000
/* 319299 0x801DD7CC */ .word	0x00000000
