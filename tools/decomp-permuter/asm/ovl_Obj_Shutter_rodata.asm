.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objShutterOverlayInfo
/* 000160 0x80A38150 */ .word	0x00000240
/* 000161 0x80A38154 */ .word	0x00000030
/* 000162 0x80A38158 */ .word	0x00000010
/* 000163 0x80A3815C */ .word	0x00000000
/* 000164 0x80A38160 */ .word	0x0000000A
glabel objShutterOverlayRelocations
/* 000165 0x80A38164 */ .word	0x45000030
/* 000166 0x80A38168 */ .word	0x46000034
/* 000167 0x80A3816C */ .word	0x45000100
/* 000168 0x80A38170 */ .word	0x4600012C
/* 000169 0x80A38174 */ .word	0x4500019C
/* 000170 0x80A38178 */ .word	0x460001A0
/* 000171 0x80A3817C */ .word	0x82000010
/* 000172 0x80A38180 */ .word	0x82000014
/* 000173 0x80A38184 */ .word	0x82000018
/* 000174 0x80A38188 */ .word	0x8200001C
glabel objShutterOverlayInfoOffset
/* 000175 0x80A3818C */ .word	0x00000040
