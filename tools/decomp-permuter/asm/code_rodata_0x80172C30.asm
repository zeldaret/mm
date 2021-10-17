.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DFC80
/* 321648 0x801DFC80 */ .word	0x41554449
/* 321649 0x801DFC84 */ .word	0x4F205350
/* 321650 0x801DFC88 */ .word	0x2054494D
/* 321651 0x801DFC8C */ .word	0x454F5554
/* 321652 0x801DFC90 */ .word	0x20253038
/* 321653 0x801DFC94 */ .word	0x78202530
/* 321654 0x801DFC98 */ .word	0x38780A00
glabel D_801DFC9C
/* 321655 0x801DFC9C */ .word	0x61756469
/* 321656 0x801DFCA0 */ .word	0x6F4D6772
/* 321657 0x801DFCA4 */ .word	0x2E633AA4
/* 321658 0x801DFCA8 */ .word	0xE2A4A6A5
/* 321659 0x801DFCAC */ .word	0xC0A5E1A1
/* 321660 0x801DFCB0 */ .word	0xAABBE0A4
/* 321661 0x801DFCB4 */ .word	0xCCA1AA0A
/* 321662 0x801DFCB8 */ .word	0x00000000
/* 321663 0x801DFCBC */ .word	0x00000000
