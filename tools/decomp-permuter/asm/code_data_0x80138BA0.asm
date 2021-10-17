.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel identityMatrix
/* 295044 0x801C5CD0 */ .word	0x3F800000
/* 295045 0x801C5CD4 */ .word	0x00000000
/* 295046 0x801C5CD8 */ .word	0x00000000
/* 295047 0x801C5CDC */ .word	0x00000000
/* 295048 0x801C5CE0 */ .word	0x00000000
/* 295049 0x801C5CE4 */ .word	0x3F800000
/* 295050 0x801C5CE8 */ .word	0x00000000
/* 295051 0x801C5CEC */ .word	0x00000000
/* 295052 0x801C5CF0 */ .word	0x00000000
/* 295053 0x801C5CF4 */ .word	0x00000000
/* 295054 0x801C5CF8 */ .word	0x3F800000
/* 295055 0x801C5CFC */ .word	0x00000000
/* 295056 0x801C5D00 */ .word	0x00000000
/* 295057 0x801C5D04 */ .word	0x00000000
/* 295058 0x801C5D08 */ .word	0x00000000
/* 295059 0x801C5D0C */ .word	0x3F800000
