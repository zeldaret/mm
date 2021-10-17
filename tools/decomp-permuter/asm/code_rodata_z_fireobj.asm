.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DD7D0
/* 319300 0x801DD7D0 */ .word	0x45CB2000
glabel D_801DD7D4
/* 319301 0x801DD7D4 */ .word	0x45CB2000
/* 319302 0x801DD7D8 */ .word	0x00000000
/* 319303 0x801DD7DC */ .word	0x00000000
