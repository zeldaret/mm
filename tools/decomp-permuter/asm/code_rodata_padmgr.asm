.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DFD90
/* 321716 0x801DFD90 */ .word	0x2E2E2F70
/* 321717 0x801DFD94 */ .word	0x61646D67
/* 321718 0x801DFD98 */ .word	0x722E6300
glabel D_801DFD9C
/* 321719 0x801DFD9C */ .word	0x2E2E2F70
/* 321720 0x801DFDA0 */ .word	0x61646D67
/* 321721 0x801DFDA4 */ .word	0x722E6300
glabel D_801DFDA8
/* 321722 0x801DFDA8 */ .word	0xC3CEA4E9
/* 321723 0x801DFDAC */ .word	0xA4CAA4A4
/* 321724 0x801DFDB0 */ .word	0xBCEFCEE0
/* 321725 0x801DFDB4 */ .word	0xA4CEA5B3
/* 321726 0x801DFDB8 */ .word	0xA5F3A5C8
/* 321727 0x801DFDBC */ .word	0xA5EDA1BC
/* 321728 0x801DFDC0 */ .word	0xA5E92825
/* 321729 0x801DFDC4 */ .word	0x30347829
/* 321730 0x801DFDC8 */ .word	0xA4F2C7A7
/* 321731 0x801DFDCC */ .word	0xBCB1A4B7
/* 321732 0x801DFDD0 */ .word	0xA4DEA4B7
/* 321733 0x801DFDD4 */ .word	0xA4BF0000
/* 321734 0x801DFDD8 */ .word	0x00000000
/* 321735 0x801DFDDC */ .word	0x00000000
