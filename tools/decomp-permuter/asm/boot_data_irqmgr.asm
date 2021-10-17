.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel gIrqMgrResetStatus
/* 023232 0x80096B60 */ .word	0x00000000
/* 023233 0x80096B64 */ .word	0x00000000
glabel sIrqMgrResetTime
/* 023234 0x80096B68 */ .word	0x00000000
/* 023235 0x80096B6C */ .word	0x00000000
glabel sIrqMgrRetraceTime
/* 023236 0x80096B70 */ .word	0x00000000
/* 023237 0x80096B74 */ .word	0x00000000
glabel sIrqMgrRetraceCount
/* 023238 0x80096B78 */ .word	0x00000000
/* 023239 0x80096B7C */ .word	0x00000000
