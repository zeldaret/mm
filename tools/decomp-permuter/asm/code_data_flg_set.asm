.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_801AEC70
/* 271468 0x801AEC70 */ .word	0x00000000
glabel D_801AEC74
/* 271469 0x801AEC74 */ .word	0x00000000
glabel D_801AEC78
/* 271470 0x801AEC78 */ .word	0x00000000
/* 271471 0x801AEC7C */ .word	0x00000000
