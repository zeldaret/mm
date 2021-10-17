.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Demo_Syoten_InitVars
/* 001228 0x80C177B0 */ .word	0x02950700
/* 001229 0x80C177B4 */ .word	0x00000030
/* 001230 0x80C177B8 */ .word	0x026F0000
/* 001231 0x80C177BC */ .word	0x000003F8
/* 001232 0x80C177C0 */ .word	DemoSyoten_Init
/* 001233 0x80C177C4 */ .word	DemoSyoten_Destroy
/* 001234 0x80C177C8 */ .word	DemoSyoten_Update
/* 001235 0x80C177CC */ .word	DemoSyoten_Draw
glabel D_80C177D0
/* 001236 0x80C177D0 */ .byte	0x00
glabel D_80C177D1
/* 001236 0x80C177D0 */ .byte	0x01
/* 001236 0x80C177D0 */ .short	0x0100
/* 001237 0x80C177D4 */ .word	0x02020202
/* 001238 0x80C177D8 */ .word	0x00000100
/* 001239 0x80C177DC */ .word	0x02020001
/* 001240 0x80C177E0 */ .word	0x00020200
/* 001241 0x80C177E4 */ .word	0x01000202
/* 001242 0x80C177E8 */ .word	0x00010002
/* 001243 0x80C177EC */ .word	0x02000100
/* 001244 0x80C177F0 */ .word	0x01020201
/* 001245 0x80C177F4 */ .word	0x02020000
/* 001246 0x80C177F8 */ .word	0x00010100
/* 001247 0x80C177FC */ .word	0x02020202
/* 001248 0x80C17800 */ .word	0x00000100
/* 001249 0x80C17804 */ .word	0x02020001
/* 001250 0x80C17808 */ .word	0x00020200
/* 001251 0x80C1780C */ .word	0x01000202
/* 001252 0x80C17810 */ .word	0x02000002
/* 001253 0x80C17814 */ .word	0x00010100
/* 001254 0x80C17818 */ .word	0x02020200
/* 001255 0x80C1781C */ .word	0x01000202
glabel D_80C17820
/* 001256 0x80C17820 */ .byte	0x00
glabel D_80C17821
/* 001256 0x80C17820 */ .byte	0x00
/* 001256 0x80C17820 */ .short	0x0000
glabel D_80C17824
/* 001257 0x80C17824 */ .word	0xA06482FF
/* 001258 0x80C17828 */ .word	0x9678A0FF
/* 001259 0x80C1782C */ .word	0x825A96FF
/* 001260 0x80C17830 */ .word	0x5A4678FF
glabel D_80C17834
/* 001261 0x80C17834 */ .word	0x6E3250FF
/* 001262 0x80C17838 */ .word	0x786482FF
/* 001263 0x80C1783C */ .word	0x5A2864FF
/* 001264 0x80C17840 */ .word	0x3C3264FF
/* 001265 0x80C17844 */ .word	0x00000000
/* 001266 0x80C17848 */ .word	0x00000000
/* 001267 0x80C1784C */ .word	0x00000000
