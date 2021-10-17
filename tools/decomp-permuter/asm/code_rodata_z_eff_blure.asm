.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_801DC080
/* 317808 0x801DC080 */ .word	0x3C03126F
glabel D_801DC084
/* 317809 0x801DC084 */ .word	0x3F350481
glabel jtbl_D_801DC088
/* 317810 0x801DC088 */ .word	L800A91A4
/* 317811 0x801DC08C */ .word	L800A8E34
/* 317812 0x801DC090 */ .word	L800A8EA4
/* 317813 0x801DC094 */ .word	L800A8F1C
/* 317814 0x801DC098 */ .word	L800A8FCC
glabel D_801DC09C
/* 317815 0x801DC09C */ .word	0x3DCCCCCD
glabel D_801DC0A0
/* 317816 0x801DC0A0 */ .word	0x3A03126F
/* 317817 0x801DC0A4 */ .word	0x00000000
/* 317818 0x801DC0A8 */ .word	0x00000000
/* 317819 0x801DC0AC */ .word	0x00000000
