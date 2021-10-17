.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel padmgrContext
/* 306844 0x801D1530 */ .word	D_801FB620
glabel controllerInputsCaptured
/* 306845 0x801D1534 */ .word	0x00000000
glabel D_801D1538
/* 306846 0x801D1538 */ .word	0x00000001
/* 306847 0x801D153C */ .word	0x00000000
