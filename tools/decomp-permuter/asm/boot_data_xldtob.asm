.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel ldigs
/* 024628 0x80098130 */ .word	0x30313233
/* 024629 0x80098134 */ .word	0x34353637
/* 024630 0x80098138 */ .word	0x38396162
/* 024631 0x8009813C */ .word	0x63646566
/* 024632 0x80098140 */ .word	0x00000000
glabel udigs
/* 024633 0x80098144 */ .word	0x30313233
/* 024634 0x80098148 */ .word	0x34353637
/* 024635 0x8009814C */ .word	0x38394142
/* 024636 0x80098150 */ .word	0x43444546
/* 024637 0x80098154 */ .word	0x00000000
/* 024638 0x80098158 */ .word	0x00000000
/* 024639 0x8009815C */ .word	0x00000000
