.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Demo_heishi_InitVars
/* 000328 0x80BE9A30 */ .word	0x026E0400
/* 000329 0x80BE9A34 */ .word	0x00000009
/* 000330 0x80BE9A38 */ .word	0x01B60000
/* 000331 0x80BE9A3C */ .word	0x000002C0
/* 000332 0x80BE9A40 */ .word	EnDemoheishi_Init
/* 000333 0x80BE9A44 */ .word	EnDemoheishi_Destroy
/* 000334 0x80BE9A48 */ .word	EnDemoheishi_Update
/* 000335 0x80BE9A4C */ .word	EnDemoheishi_Draw
glabel D_80BE9A50
/* 000336 0x80BE9A50 */ .word	0x0A000039
/* 000337 0x80BE9A54 */ .word	0x20010000
/* 000338 0x80BE9A58 */ .word	0x00000000
/* 000339 0x80BE9A5C */ .word	0x00000000
/* 000340 0x80BE9A60 */ .word	0x00000000
/* 000341 0x80BE9A64 */ .word	0xF7CFFFFF
/* 000342 0x80BE9A68 */ .word	0x00000000
/* 000343 0x80BE9A6C */ .word	0x00000100
/* 000344 0x80BE9A70 */ .word	0x00280028
/* 000345 0x80BE9A74 */ .word	0x00000000
/* 000346 0x80BE9A78 */ .word	0x00000000
glabel D_80BE9A7C
/* 000347 0x80BE9A7C */ .word	0x14730000
glabel D_80BE9A80
/* 000348 0x80BE9A80 */ .word	0x06006C18
/* 000349 0x80BE9A84 */ .word	0x06002A84
/* 000350 0x80BE9A88 */ .word	0x06003BFC
/* 000351 0x80BE9A8C */ .word	0x06003380
/* 000352 0x80BE9A90 */ .word	0x06004770
glabel D_80BE9A94
/* 000353 0x80BE9A94 */ .word	0x00000000
/* 000354 0x80BE9A98 */ .word	0x02000000
/* 000355 0x80BE9A9C */ .word	0x00000000
