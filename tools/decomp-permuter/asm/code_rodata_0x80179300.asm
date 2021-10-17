.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801E0120
/* 321944 0x801E0120 */ .word	0x4622F983
glabel D_801E0124
/* 321945 0x801E0124 */ .word	0x38000100
glabel D_801E0128
/* 321946 0x801E0128 */ .word	0x4622F983
glabel D_801E012C
/* 321947 0x801E012C */ .word	0x38000100
