.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Muto_InitVars
/* 000572 0x80BE83F0 */ .word	0x026B0400
/* 000573 0x80BE83F4 */ .word	0x00000009
/* 000574 0x80BE83F8 */ .word	0x00F00000
/* 000575 0x80BE83FC */ .word	0x000002E0
/* 000576 0x80BE8400 */ .word	EnMuto_Init
/* 000577 0x80BE8404 */ .word	EnMuto_Destroy
/* 000578 0x80BE8408 */ .word	EnMuto_Update
/* 000579 0x80BE840C */ .word	EnMuto_Draw
glabel D_80BE8410
/* 000580 0x80BE8410 */ .word	0x2ABD2ABB
/* 000581 0x80BE8414 */ .word	0x06240623
/* 000582 0x80BE8418 */ .word	0x2AC60000
glabel D_80BE841C
/* 000583 0x80BE841C */ .word	0x0A000039
/* 000584 0x80BE8420 */ .word	0x20010000
/* 000585 0x80BE8424 */ .word	0x00000000
/* 000586 0x80BE8428 */ .word	0x00000000
/* 000587 0x80BE842C */ .word	0x00000000
/* 000588 0x80BE8430 */ .word	0xF7CFFFFF
/* 000589 0x80BE8434 */ .word	0x00000000
/* 000590 0x80BE8438 */ .word	0x00000100
/* 000591 0x80BE843C */ .word	0x0014003C
/* 000592 0x80BE8440 */ .word	0x00000000
/* 000593 0x80BE8444 */ .word	0x00000000
glabel D_80BE8448
/* 000594 0x80BE8448 */ .word	0x06000E50
/* 000595 0x80BE844C */ .word	0x06000E50
glabel D_80BE8450
/* 000596 0x80BE8450 */ .word	0x00020000
/* 000597 0x80BE8454 */ .word	0x00000000
/* 000598 0x80BE8458 */ .word	0x00000000
/* 000599 0x80BE845C */ .word	0x00000000
