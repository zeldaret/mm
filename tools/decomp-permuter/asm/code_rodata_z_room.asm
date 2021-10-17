.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DDFA0
/* 319800 0x801DDFA0 */ .word	0x2E2E2F7A
/* 319801 0x801DDFA4 */ .word	0x5F726F6F
/* 319802 0x801DDFA8 */ .word	0x6D2E6300
glabel D_801DDFAC
/* 319803 0x801DDFAC */ .word	0x2E2E2F7A
/* 319804 0x801DDFB0 */ .word	0x5F726F6F
/* 319805 0x801DDFB4 */ .word	0x6D2E6300
glabel D_801DDFB8
/* 319806 0x801DDFB8 */ .word	0x2E2E2F7A
/* 319807 0x801DDFBC */ .word	0x5F726F6F
/* 319808 0x801DDFC0 */ .word	0x6D2E6300
glabel D_801DDFC4
/* 319809 0x801DDFC4 */ .word	0x7F7FFFFF
glabel D_801DDFC8
/* 319810 0x801DDFC8 */ .word	0x3F19999A
glabel D_801DDFCC
/* 319811 0x801DDFCC */ .word	0x3F99999A
glabel D_801DDFD0
/* 319812 0x801DDFD0 */ .word	0x4019999A
glabel D_801DDFD4
/* 319813 0x801DDFD4 */ .word	0x3E99999A
glabel D_801DDFD8
/* 319814 0x801DDFD8 */ .word	0x3F19999A
glabel D_801DDFDC
/* 319815 0x801DDFDC */ .word	0x3F99999A
glabel D_801DDFE0
/* 319816 0x801DDFE0 */ .word	0x4019999A
glabel D_801DDFE4
/* 319817 0x801DDFE4 */ .word	0x3E99999A
/* 319818 0x801DDFE8 */ .word	0x00000000
/* 319819 0x801DDFEC */ .word	0x00000000
