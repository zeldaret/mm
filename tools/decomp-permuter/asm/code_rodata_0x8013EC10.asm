.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DF090
/* 320884 0x801DF090 */ .word	0x49742400
glabel D_801DF094
/* 320885 0x801DF094 */ .word	0x49742400
/* 320886 0x801DF098 */ .word	0x00000000
/* 320887 0x801DF09C */ .word	0x00000000
