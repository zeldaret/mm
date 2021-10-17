.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel jtbl_D_801DD790
/* 319284 0x801DD790 */ .word	L800F1494
/* 319285 0x801DD794 */ .word	L800F149C
/* 319286 0x801DD798 */ .word	L800F14A4
/* 319287 0x801DD79C */ .word	L800F14AC
/* 319288 0x801DD7A0 */ .word	L800F14B4
/* 319289 0x801DD7A4 */ .word	L800F14BC
/* 319290 0x801DD7A8 */ .word	L800F14C4
/* 319291 0x801DD7AC */ .word	L800F14CC
