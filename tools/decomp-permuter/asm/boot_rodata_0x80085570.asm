.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel jtbl_D_80099090
/* 025612 0x80099090 */ .word	L80085F08
/* 025613 0x80099094 */ .word	L80085EF0
/* 025614 0x80099098 */ .word	L80085EE0
/* 025615 0x8009909C */ .word	L80085ED0
/* 025616 0x800990A0 */ .word	L80085F1C
/* 025617 0x800990A4 */ .word	0x00000000
/* 025618 0x800990A8 */ .word	0x00000000
/* 025619 0x800990AC */ .word	0x00000000
