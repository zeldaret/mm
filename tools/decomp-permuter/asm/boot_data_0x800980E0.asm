.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_800980E0
/* 024608 0x800980E0 */ .word	0x2C000000
/* 024609 0x800980E4 */ .word	0x0000311E
/* 024610 0x800980E8 */ .word	0x00000140
/* 024611 0x800980EC */ .word	0x04541E3A
/* 024612 0x800980F0 */ .word	0x00000271
/* 024613 0x800980F4 */ .word	0x00170C69
/* 024614 0x800980F8 */ .word	0x0C6F0C6D
/* 024615 0x800980FC */ .word	0x00800300
/* 024616 0x80098100 */ .word	0x00000200
/* 024617 0x80098104 */ .word	0x00000000
/* 024618 0x80098108 */ .word	0x00000280
/* 024619 0x8009810C */ .word	0x00000400
/* 024620 0x80098110 */ .word	0x002F0269
/* 024621 0x80098114 */ .word	0x0009026B
/* 024622 0x80098118 */ .word	0x00000002
/* 024623 0x8009811C */ .word	0x00000280
/* 024624 0x80098120 */ .word	0x00000400
/* 024625 0x80098124 */ .word	0x002F0269
/* 024626 0x80098128 */ .word	0x0009026B
/* 024627 0x8009812C */ .word	0x00000002
