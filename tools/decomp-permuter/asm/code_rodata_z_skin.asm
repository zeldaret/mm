.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DE5C0
/* 320192 0x801DE5C0 */ .word	0x3C23D70A
/* 320193 0x801DE5C4 */ .word	0x00000000
/* 320194 0x801DE5C8 */ .word	0x00000000
/* 320195 0x801DE5CC */ .word	0x00000000
