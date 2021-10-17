.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel spaces
/* 024496 0x80097F20 */ .word	0x20202020
/* 024497 0x80097F24 */ .word	0x20202020
/* 024498 0x80097F28 */ .word	0x20202020
/* 024499 0x80097F2C */ .word	0x20202020
/* 024500 0x80097F30 */ .word	0x20202020
/* 024501 0x80097F34 */ .word	0x20202020
/* 024502 0x80097F38 */ .word	0x20202020
/* 024503 0x80097F3C */ .word	0x20202020
/* 024504 0x80097F40 */ .word	0x00000000
glabel zeroes
/* 024505 0x80097F44 */ .word	0x30303030
/* 024506 0x80097F48 */ .word	0x30303030
/* 024507 0x80097F4C */ .word	0x30303030
/* 024508 0x80097F50 */ .word	0x30303030
/* 024509 0x80097F54 */ .word	0x30303030
/* 024510 0x80097F58 */ .word	0x30303030
/* 024511 0x80097F5C */ .word	0x30303030
/* 024512 0x80097F60 */ .word	0x30303030
/* 024513 0x80097F64 */ .word	0x00000000
/* 024514 0x80097F68 */ .word	0x00000000
/* 024515 0x80097F6C */ .word	0x00000000
