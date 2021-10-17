.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel En_Encount4_InitVars
/* 000480 0x809C46B0 */ .word	0x011B0600
/* 000481 0x809C46B4 */ .word	0x08000010
/* 000482 0x809C46B8 */ .word	0x00010000
/* 000483 0x809C46BC */ .word	0x00000158
/* 000484 0x809C46C0 */ .word	EnEncount4_Init
/* 000485 0x809C46C4 */ .word	EnEncount4_Destroy
/* 000486 0x809C46C8 */ .word	EnEncount4_Update
/* 000487 0x809C46CC */ .word	0x00000000
glabel D_809C46D0
/* 000488 0x809C46D0 */ .word	0x4000C000
/* 000489 0x809C46D4 */ .word	0x40000000
/* 000490 0x809C46D8 */ .word	0xC0000000
glabel D_809C46DC
/* 000491 0x809C46DC */ .word	0x43480000
/* 000492 0x809C46E0 */ .word	0x43480000
/* 000493 0x809C46E4 */ .word	0x42C80000
/* 000494 0x809C46E8 */ .word	0x00000000
/* 000495 0x809C46EC */ .word	0x42C80000
