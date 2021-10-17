.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

/* 004240 0x80A10A50 */ .word	0x2E2E2F7A
/* 004241 0x80A10A54 */ .word	0x5F656E5F
/* 004242 0x80A10A58 */ .word	0x736F4231
/* 004243 0x80A10A5C */ .word	0x2E630000
/* 004244 0x80A10A60 */ .word	0x2E2E2F7A
/* 004245 0x80A10A64 */ .word	0x5F656E5F
/* 004246 0x80A10A68 */ .word	0x736F4231
/* 004247 0x80A10A6C */ .word	0x2E630000
