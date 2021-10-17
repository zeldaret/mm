.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_801C5DD0
/* 295108 0x801C5DD0 */ .word	0xEF000000
/* 295109 0x801C5DD4 */ .word	0x0FA54044
/* 295110 0x801C5DD8 */ .word	0xDE010000
/* 295111 0x801C5DDC */ .word	0x0E0002E0
glabel D_801C5DE0
/* 295112 0x801C5DE0 */ .word	0xEF000000
/* 295113 0x801C5DE4 */ .word	0xF5554044
/* 295114 0x801C5DE8 */ .word	0xDE010000
/* 295115 0x801C5DEC */ .word	0x0E0002E0
glabel D_801C5DF0
/* 295116 0x801C5DF0 */ .word	0xEF000000
/* 295117 0x801C5DF4 */ .word	0x0F554044
/* 295118 0x801C5DF8 */ .word	0xDE010000
/* 295119 0x801C5DFC */ .word	0x0E0002E0
glabel D_801C5E00
/* 295120 0x801C5E00 */ .word	0xFCFFFFFF
/* 295121 0x801C5E04 */ .word	0xFFFDF6FB
/* 295122 0x801C5E08 */ .word	0xEF0000D0
/* 295123 0x801C5E0C */ .word	0x00504344
/* 295124 0x801C5E10 */ .word	0xDE000000
/* 295125 0x801C5E14 */ .word	0x0E0002E0
/* 295126 0x801C5E18 */ .word	0xEF000000
/* 295127 0x801C5E1C */ .word	0x0F554044
/* 295128 0x801C5E20 */ .word	0xDE010000
/* 295129 0x801C5E24 */ .word	0x0E0002E0
/* 295130 0x801C5E28 */ .word	0x00000000
/* 295131 0x801C5E2C */ .word	0x00000000
