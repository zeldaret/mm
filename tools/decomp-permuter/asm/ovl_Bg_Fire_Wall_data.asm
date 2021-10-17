.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Bg_Fire_Wall_InitVars
/* 000484 0x809ACC40 */ .word	0x01100100
/* 000485 0x809ACC44 */ .word	0x00000000
/* 000486 0x809ACC48 */ .word	0x01530000
/* 000487 0x809ACC4C */ .word	0x000001B0
/* 000488 0x809ACC50 */ .word	BgFireWall_Init
/* 000489 0x809ACC54 */ .word	BgFireWall_Destroy
/* 000490 0x809ACC58 */ .word	BgFireWall_Update
/* 000491 0x809ACC5C */ .word	0x00000000
glabel D_809ACC60
/* 000492 0x809ACC60 */ .word	0x0A110009
/* 000493 0x809ACC64 */ .word	0x20010000
/* 000494 0x809ACC68 */ .word	0x00000000
/* 000495 0x809ACC6C */ .word	0x20000000
/* 000496 0x809ACC70 */ .word	0x01040000
/* 000497 0x809ACC74 */ .word	0xF7CFFFFF
/* 000498 0x809ACC78 */ .word	0x00000000
/* 000499 0x809ACC7C */ .word	0x19000100
/* 000500 0x809ACC80 */ .word	0x00220055
/* 000501 0x809ACC84 */ .word	0x00000000
/* 000502 0x809ACC88 */ .word	0x00000000
glabel D_809ACC8C
/* 000503 0x809ACC8C */ .word	0x01000050
/* 000504 0x809ACC90 */ .word	0x0064FF00
glabel D_809ACC94
/* 000505 0x809ACC94 */ .word	0x06003CA0
/* 000506 0x809ACC98 */ .word	0x060040A0
/* 000507 0x809ACC9C */ .word	0x060044A0
/* 000508 0x809ACCA0 */ .word	0x060048A0
/* 000509 0x809ACCA4 */ .word	0x06004CA0
/* 000510 0x809ACCA8 */ .word	0x060050A0
/* 000511 0x809ACCAC */ .word	0x060054A0
/* 000512 0x809ACCB0 */ .word	0x060058A0
/* 000513 0x809ACCB4 */ .word	0x00000000
/* 000514 0x809ACCB8 */ .word	0x00000000
/* 000515 0x809ACCBC */ .word	0x00000000
