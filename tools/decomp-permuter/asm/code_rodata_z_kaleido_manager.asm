.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DF9C0
/* 321472 0x801DF9C0 */ .word	0x6B616C65
/* 321473 0x801DF9C4 */ .word	0x69646F5F
/* 321474 0x801DF9C8 */ .word	0x73636F70
/* 321475 0x801DF9CC */ .word	0x65000000
glabel D_801DF9D0
/* 321476 0x801DF9D0 */ .word	0x706C6179
/* 321477 0x801DF9D4 */ .word	0x65725F61
/* 321478 0x801DF9D8 */ .word	0x63746F72
/* 321479 0x801DF9DC */ .word	0x00000000
