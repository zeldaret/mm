.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_801C0EC0
/* 290048 0x801C0EC0 */ .word	0x00010000
glabel sQuakeRequestCount
/* 290049 0x801C0EC4 */ .word	0x00000000
glabel sQuakeCallbacks
/* 290050 0x801C0EC8 */ .word	0x00000000
/* 290051 0x801C0ECC */ .word	Quake_Callback1
/* 290052 0x801C0ED0 */ .word	Quake_Callback2
/* 290053 0x801C0ED4 */ .word	Quake_Callback3
/* 290054 0x801C0ED8 */ .word	Quake_Callback4
/* 290055 0x801C0EDC */ .word	Quake_Callback5
/* 290056 0x801C0EE0 */ .word	Quake_Callback6
glabel D_801C0EE4
/* 290057 0x801C0EE4 */ .word	0x03F00000
glabel D_801C0EE8
/* 290058 0x801C0EE8 */ .word	0x01560000
glabel D_801C0EEC
/* 290059 0x801C0EEC */ .word	0x00010000
