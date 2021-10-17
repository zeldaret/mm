.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_800994C0
/* 025880 0x800994C0 */ .word	0x80000000
/* 025881 0x800994C4 */ .word	0x00000000
glabel D_800994C8
/* 025882 0x800994C8 */ .word	0x80000000
/* 025883 0x800994CC */ .word	0x00000000
