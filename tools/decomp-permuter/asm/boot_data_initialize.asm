.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel osClockRate
/* 024444 0x80097E50 */ .word	0x00000000
/* 024445 0x80097E54 */ .word	0x03B9ACA0
glabel osViClock
/* 024446 0x80097E58 */ .word	0x02E6D354
glabel __osShutdown
/* 024447 0x80097E5C */ .word	0x00000000
glabel __OSGlobalIntMask
/* 024448 0x80097E60 */ .word	0x003FFF01
/* 024449 0x80097E64 */ .word	0x00000000
/* 024450 0x80097E68 */ .word	0x00000000
/* 024451 0x80097E6C */ .word	0x00000000
