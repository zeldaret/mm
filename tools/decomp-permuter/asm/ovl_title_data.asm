.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel titleRotation
/* 000536 0x80800860 */ .word	0x00000000
/* 000537 0x80800864 */ .word	0x00000000
glabel D_80800868
/* 000538 0x80800868 */ .word	0x64646400
/* 000539 0x8080086C */ .word	0x64646400
glabel D_80800870
/* 000540 0x80800870 */ .word	0xFFFFFF00
/* 000541 0x80800874 */ .word	0xFFFFFF00
/* 000542 0x80800878 */ .word	0x45454500
/* 000543 0x8080087C */ .word	0x00000000
