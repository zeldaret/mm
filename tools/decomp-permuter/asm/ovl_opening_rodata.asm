.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel openingOverlayBlockInfo
/* 000120 0x80803FD0 */ .word	0x000001D0
/* 000121 0x80803FD4 */ .word	0x00000010
/* 000122 0x80803FD8 */ .word	0x00000000
/* 000123 0x80803FDC */ .word	0x00000000
/* 000124 0x80803FE0 */ .word	0x0000000A
glabel openingOverlayRelocations
/* 000125 0x80803FE4 */ .word	0x45000034
/* 000126 0x80803FE8 */ .word	0x46000044
/* 000127 0x80803FEC */ .word	0x4500004C
/* 000128 0x80803FF0 */ .word	0x46000058
/* 000129 0x80803FF4 */ .word	0x440000FC
/* 000130 0x80803FF8 */ .word	0x44000104
/* 000131 0x80803FFC */ .word	0x45000178
/* 000132 0x80804000 */ .word	0x46000184
/* 000133 0x80804004 */ .word	0x4500017C
/* 000134 0x80804008 */ .word	0x46000188
glabel openingOverlayBlockInfoOffset
/* 000135 0x8080400C */ .word	0x00000040
