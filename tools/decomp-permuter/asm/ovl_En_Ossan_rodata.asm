.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

/* 004236 0x808AC2D0 */ .word	0x2E2E2F7A
/* 004237 0x808AC2D4 */ .word	0x5F656E5F
/* 004238 0x808AC2D8 */ .word	0x6F42312E
/* 004239 0x808AC2DC */ .word	0x63000000
/* 004240 0x808AC2E0 */ .word	0x2E2E2F7A
/* 004241 0x808AC2E4 */ .word	0x5F656E5F
/* 004242 0x808AC2E8 */ .word	0x6F42312E
/* 004243 0x808AC2EC */ .word	0x63000000
/* 004244 0x808AC2F0 */ .word	0x2E2E2F7A
/* 004245 0x808AC2F4 */ .word	0x5F656E5F
/* 004246 0x808AC2F8 */ .word	0x6F42312E
/* 004247 0x808AC2FC */ .word	0x63000000
