.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Demo_Moonend_InitVars
/* 000408 0x80C18070 */ .word	0x02960700
/* 000409 0x80C18074 */ .word	0x00000030
/* 000410 0x80C18078 */ .word	0x02700000
/* 000411 0x80C1807C */ .word	0x000002E4
/* 000412 0x80C18080 */ .word	DemoMoonend_Init
/* 000413 0x80C18084 */ .word	DemoMoonend_Destroy
/* 000414 0x80C18088 */ .word	DemoMoonend_Update
/* 000415 0x80C1808C */ .word	DemoMoonend_Draw
