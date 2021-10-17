.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Door_Warp1_InitVars
/* 003492 0x808BBB20 */ .word	0x00380700
/* 003493 0x808BBB24 */ .word	0x00000000
/* 003494 0x808BBB28 */ .word	0x003E0000
/* 003495 0x808BBB2C */ .word	0x0000020C
/* 003496 0x808BBB30 */ .word	DoorWarp1_Init
/* 003497 0x808BBB34 */ .word	DoorWarp1_Destroy
/* 003498 0x808BBB38 */ .word	DoorWarp1_Update
/* 003499 0x808BBB3C */ .word	DoorWarp1_Draw
glabel D_808BBB40
/* 003500 0x808BBB40 */ .word	0xC85803E8
/* 003501 0x808BBB44 */ .word	0xB0FC0FA0
/* 003502 0x808BBB48 */ .word	0xB1000320
/* 003503 0x808BBB4C */ .word	0x31040FA0
glabel D_808BBB50
/* 003504 0x808BBB50 */ .word	0x32960064
/* 003505 0x808BBB54 */ .word	0x96C80032
/* 003506 0x808BBB58 */ .word	0xC8789600
glabel D_808BBB5C
/* 003507 0x808BBB5C */ .word	0x00000000
/* 003508 0x808BBB60 */ .word	0x3D4CCCCD
glabel D_808BBB64
/* 003509 0x808BBB64 */ .word	0x00000000
glabel D_808BBB68
/* 003510 0x808BBB68 */ .word	0x00000000
glabel D_808BBB6C
/* 003511 0x808BBB6C */ .word	0x3E800000
/* 003512 0x808BBB70 */ .word	0x00000000
/* 003513 0x808BBB74 */ .word	0x00000000
/* 003514 0x808BBB78 */ .word	0x00000000
/* 003515 0x808BBB7C */ .word	0x00000000
