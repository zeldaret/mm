.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objKepnKoyaOverlayInfo
/* 000076 0x80C07C50 */ .word	0x00000100
/* 000077 0x80C07C54 */ .word	0x00000030
/* 000078 0x80C07C58 */ .word	0x00000000
/* 000079 0x80C07C5C */ .word	0x00000000
/* 000080 0x80C07C60 */ .word	0x00000006
glabel objKepnKoyaOverlayRelocations
/* 000081 0x80C07C64 */ .word	0x45000014
/* 000082 0x80C07C68 */ .word	0x46000018
/* 000083 0x80C07C6C */ .word	0x82000010
/* 000084 0x80C07C70 */ .word	0x82000014
/* 000085 0x80C07C74 */ .word	0x82000018
/* 000086 0x80C07C78 */ .word	0x8200001C
glabel objKepnKoyaOverlayInfoOffset
/* 000087 0x80C07C7C */ .word	0x00000030
