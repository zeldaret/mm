.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enGamelupyOverlayInfo
/* 000380 0x80AF6D50 */ .word	0x00000570
/* 000381 0x80AF6D54 */ .word	0x00000070
/* 000382 0x80AF6D58 */ .word	0x00000010
/* 000383 0x80AF6D5C */ .word	0x00000000
/* 000384 0x80AF6D60 */ .word	0x0000001D
glabel enGamelupyOverlayRelocations
/* 000385 0x80AF6D64 */ .word	0x45000058
/* 000386 0x80AF6D68 */ .word	0x46000060
/* 000387 0x80AF6D6C */ .word	0x440000AC
/* 000388 0x80AF6D70 */ .word	0x45000150
/* 000389 0x80AF6D74 */ .word	0x46000154
/* 000390 0x80AF6D78 */ .word	0x45000164
/* 000391 0x80AF6D7C */ .word	0x4600016C
/* 000392 0x80AF6D80 */ .word	0x45000170
/* 000393 0x80AF6D84 */ .word	0x46000180
/* 000394 0x80AF6D88 */ .word	0x45000178
/* 000395 0x80AF6D8C */ .word	0x4600017C
/* 000396 0x80AF6D90 */ .word	0x450001E4
/* 000397 0x80AF6D94 */ .word	0x460001E8
/* 000398 0x80AF6D98 */ .word	0x4400021C
/* 000399 0x80AF6D9C */ .word	0x45000234
/* 000400 0x80AF6DA0 */ .word	0x46000238
/* 000401 0x80AF6DA4 */ .word	0x440002B4
/* 000402 0x80AF6DA8 */ .word	0x450002FC
/* 000403 0x80AF6DAC */ .word	0x46000300
/* 000404 0x80AF6DB0 */ .word	0x45000388
/* 000405 0x80AF6DB4 */ .word	0x460003A0
/* 000406 0x80AF6DB8 */ .word	0x440003BC
/* 000407 0x80AF6DBC */ .word	0x4400047C
/* 000408 0x80AF6DC0 */ .word	0x45000518
/* 000409 0x80AF6DC4 */ .word	0x46000530
/* 000410 0x80AF6DC8 */ .word	0x82000010
/* 000411 0x80AF6DCC */ .word	0x82000014
/* 000412 0x80AF6DD0 */ .word	0x82000018
/* 000413 0x80AF6DD4 */ .word	0x8200001C
/* 000414 0x80AF6DD8 */ .word	0x00000000
glabel enGamelupyOverlayInfoOffset
/* 000415 0x80AF6DDC */ .word	0x00000090
