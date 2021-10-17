.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgLotusOverlayInfo
/* 000376 0x80AD6D40 */ .word	0x00000590
/* 000377 0x80AD6D44 */ .word	0x00000030
/* 000378 0x80AD6D48 */ .word	0x00000020
/* 000379 0x80AD6D4C */ .word	0x00000000
/* 000380 0x80AD6D50 */ .word	0x0000001C
glabel bgLotusOverlayRelocations
/* 000381 0x80AD6D54 */ .word	0x45000014
/* 000382 0x80AD6D58 */ .word	0x46000018
/* 000383 0x80AD6D5C */ .word	0x45000074
/* 000384 0x80AD6D60 */ .word	0x4600007C
/* 000385 0x80AD6D64 */ .word	0x450000E8
/* 000386 0x80AD6D68 */ .word	0x460000EC
/* 000387 0x80AD6D6C */ .word	0x45000118
/* 000388 0x80AD6D70 */ .word	0x4600011C
/* 000389 0x80AD6D74 */ .word	0x45000130
/* 000390 0x80AD6D78 */ .word	0x46000134
/* 000391 0x80AD6D7C */ .word	0x45000138
/* 000392 0x80AD6D80 */ .word	0x4600013C
/* 000393 0x80AD6D84 */ .word	0x45000194
/* 000394 0x80AD6D88 */ .word	0x460001A4
/* 000395 0x80AD6D8C */ .word	0x450002D4
/* 000396 0x80AD6D90 */ .word	0x460002D8
/* 000397 0x80AD6D94 */ .word	0x4400030C
/* 000398 0x80AD6D98 */ .word	0x440003A0
/* 000399 0x80AD6D9C */ .word	0x450003E4
/* 000400 0x80AD6DA0 */ .word	0x460003E8
/* 000401 0x80AD6DA4 */ .word	0x45000450
/* 000402 0x80AD6DA8 */ .word	0x46000454
/* 000403 0x80AD6DAC */ .word	0x45000494
/* 000404 0x80AD6DB0 */ .word	0x460004A8
/* 000405 0x80AD6DB4 */ .word	0x82000010
/* 000406 0x80AD6DB8 */ .word	0x82000014
/* 000407 0x80AD6DBC */ .word	0x82000018
/* 000408 0x80AD6DC0 */ .word	0x8200001C
/* 000409 0x80AD6DC4 */ .word	0x00000000
/* 000410 0x80AD6DC8 */ .word	0x00000000
glabel bgLotusOverlayInfoOffset
/* 000411 0x80AD6DCC */ .word	0x00000090
