.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enRsnOverlayInfo
/* 000192 0x80C26040 */ .word	0x000002B0
/* 000193 0x80C26044 */ .word	0x00000050
/* 000194 0x80C26048 */ .word	0x00000000
/* 000195 0x80C2604C */ .word	0x00000000
/* 000196 0x80C26050 */ .word	0x0000000F
glabel enRsnOverlayRelocations
/* 000197 0x80C26054 */ .word	0x45000010
/* 000198 0x80C26058 */ .word	0x46000014
/* 000199 0x80C2605C */ .word	0x45000028
/* 000200 0x80C26060 */ .word	0x4600002C
/* 000201 0x80C26064 */ .word	0x440000B8
/* 000202 0x80C26068 */ .word	0x450001C8
/* 000203 0x80C2606C */ .word	0x460001CC
/* 000204 0x80C26070 */ .word	0x45000260
/* 000205 0x80C26074 */ .word	0x4600027C
/* 000206 0x80C26078 */ .word	0x45000274
/* 000207 0x80C2607C */ .word	0x46000278
/* 000208 0x80C26080 */ .word	0x82000010
/* 000209 0x80C26084 */ .word	0x82000014
/* 000210 0x80C26088 */ .word	0x82000018
/* 000211 0x80C2608C */ .word	0x8200001C
/* 000212 0x80C26090 */ .word	0x00000000
/* 000213 0x80C26094 */ .word	0x00000000
/* 000214 0x80C26098 */ .word	0x00000000
/* 000215 0x80C2609C */ .word	0x00000060
