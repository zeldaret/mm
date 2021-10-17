.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

/* 001524 0x808E3DD0 */ .word	0xC8BFBCCD
/* 001525 0x808E3DD4 */ .word	0xB8F720C8
/* 001526 0x808E3DD8 */ .word	0xAFC0B8BC
/* 001527 0x808E3DDC */ .word	0xBAC7D400
