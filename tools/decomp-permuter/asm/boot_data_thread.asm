.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel __osThreadTail
/* 024428 0x80097E10 */ .word	0x00000000
/* 024429 0x80097E14 */ .word	0xFFFFFFFF
glabel __osRunQueue
/* 024430 0x80097E18 */ .word	__osThreadTail
glabel __osActiveQueue
/* 024431 0x80097E1C */ .word	__osThreadTail
glabel __osRunningThread
/* 024432 0x80097E20 */ .word	0x00000000
glabel __osFaultedThread
/* 024433 0x80097E24 */ .word	0x00000000
/* 024434 0x80097E28 */ .word	0x00000000
/* 024435 0x80097E2C */ .word	0x00000000
