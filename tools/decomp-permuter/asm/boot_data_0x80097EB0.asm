.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel osViModeNtscHpn1
/* 024468 0x80097EB0 */ .word	0x08000000
/* 024469 0x80097EB4 */ .word	0x0000324E
/* 024470 0x80097EB8 */ .word	0x00000500
/* 024471 0x80097EBC */ .word	0x03E52239
/* 024472 0x80097EC0 */ .word	0x0000020C
/* 024473 0x80097EC4 */ .word	0x00000C15
/* 024474 0x80097EC8 */ .word	0x0C150C15
/* 024475 0x80097ECC */ .word	0x006C02EC
/* 024476 0x80097ED0 */ .word	0x00000400
/* 024477 0x80097ED4 */ .word	0x00000000
/* 024478 0x80097ED8 */ .word	0x00000500
/* 024479 0x80097EDC */ .word	0x00000400
/* 024480 0x80097EE0 */ .word	0x002301FD
/* 024481 0x80097EE4 */ .word	0x000E0204
/* 024482 0x80097EE8 */ .word	0x00000002
/* 024483 0x80097EEC */ .word	0x00000A00
/* 024484 0x80097EF0 */ .word	0x00000400
/* 024485 0x80097EF4 */ .word	0x002501FF
/* 024486 0x80097EF8 */ .word	0x000E0204
/* 024487 0x80097EFC */ .word	0x00000002
glabel D_80097F00
/* 024488 0x80097F00 */ .word	0xFFFFFFFF
glabel D_80097F04
/* 024489 0x80097F04 */ .word	0xFA000000
/* 024490 0x80097F08 */ .word	0x00000000
/* 024491 0x80097F0C */ .word	0x00000000
