.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bootThreadName
/* 024652 0x80098190 */ .word	0x626F6F74
/* 024653 0x80098194 */ .word	0x00000000
glabel idleThreadName
/* 024654 0x80098198 */ .word	0x69646C65
/* 024655 0x8009819C */ .word	0x00000000
