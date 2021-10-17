.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DFC70
/* 321644 0x801DFC70 */ .word	0x00010203
/* 321645 0x801DFC74 */ .short	0x0405
/* 321645 0x801DFC74 */ .byte	0x06
glabel D_801DFC77
/* 321645 0x801DFC74 */ .byte	0x00
/* 321646 0x801DFC78 */ .word	0x00000000
/* 321647 0x801DFC7C */ .word	0x00000000
