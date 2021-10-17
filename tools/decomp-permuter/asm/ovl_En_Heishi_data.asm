.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Heishi_InitVars
/* 000324 0x80BE9430 */ .word	0x026D0400
/* 000325 0x80BE9434 */ .word	0x00000009
/* 000326 0x80BE9438 */ .word	0x01B60000
/* 000327 0x80BE943C */ .word	0x000002D0
/* 000328 0x80BE9440 */ .word	EnHeishi_Init
/* 000329 0x80BE9444 */ .word	EnHeishi_Destroy
/* 000330 0x80BE9448 */ .word	EnHeishi_Update
/* 000331 0x80BE944C */ .word	EnHeishi_Draw
glabel D_80BE9450
/* 000332 0x80BE9450 */ .word	0x0A000009
/* 000333 0x80BE9454 */ .word	0x20010000
/* 000334 0x80BE9458 */ .word	0x00000000
/* 000335 0x80BE945C */ .word	0x00000000
/* 000336 0x80BE9460 */ .word	0x00000000
/* 000337 0x80BE9464 */ .word	0xF7CFFFFF
/* 000338 0x80BE9468 */ .word	0x00000000
/* 000339 0x80BE946C */ .word	0x00000100
/* 000340 0x80BE9470 */ .word	0x0014003C
/* 000341 0x80BE9474 */ .word	0x00000000
/* 000342 0x80BE9478 */ .word	0x00000000
glabel D_80BE947C
/* 000343 0x80BE947C */ .word	0x06006C18
/* 000344 0x80BE9480 */ .word	0x06002A84
/* 000345 0x80BE9484 */ .word	0x06003BFC
/* 000346 0x80BE9488 */ .word	0x06003380
/* 000347 0x80BE948C */ .word	0x06004770
glabel D_80BE9490
/* 000348 0x80BE9490 */ .word	0x00000000
/* 000349 0x80BE9494 */ .word	0x02000000
/* 000350 0x80BE9498 */ .word	0x00000000
/* 000351 0x80BE949C */ .word	0x00000000
