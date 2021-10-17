.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objHgdoorOverlayInfo
/* 000388 0x80BD46A0 */ .word	0x000005E0
/* 000389 0x80BD46A4 */ .word	0x00000030
/* 000390 0x80BD46A8 */ .word	0x00000000
/* 000391 0x80BD46AC */ .word	0x00000000
/* 000392 0x80BD46B0 */ .word	0x00000019
glabel objHgdoorOverlayRelocations
/* 000393 0x80BD46B4 */ .word	0x44000108
/* 000394 0x80BD46B8 */ .word	0x45000158
/* 000395 0x80BD46BC */ .word	0x4600015C
/* 000396 0x80BD46C0 */ .word	0x440001F0
/* 000397 0x80BD46C4 */ .word	0x440001FC
/* 000398 0x80BD46C8 */ .word	0x44000204
/* 000399 0x80BD46CC */ .word	0x4500021C
/* 000400 0x80BD46D0 */ .word	0x46000220
/* 000401 0x80BD46D4 */ .word	0x4400025C
/* 000402 0x80BD46D8 */ .word	0x44000264
/* 000403 0x80BD46DC */ .word	0x450002AC
/* 000404 0x80BD46E0 */ .word	0x460002B4
/* 000405 0x80BD46E4 */ .word	0x45000378
/* 000406 0x80BD46E8 */ .word	0x4600037C
/* 000407 0x80BD46EC */ .word	0x45000380
/* 000408 0x80BD46F0 */ .word	0x46000384
/* 000409 0x80BD46F4 */ .word	0x44000398
/* 000410 0x80BD46F8 */ .word	0x440003A8
/* 000411 0x80BD46FC */ .word	0x450003D0
/* 000412 0x80BD4700 */ .word	0x460003D4
/* 000413 0x80BD4704 */ .word	0x440004C8
/* 000414 0x80BD4708 */ .word	0x82000010
/* 000415 0x80BD470C */ .word	0x82000014
/* 000416 0x80BD4710 */ .word	0x82000018
/* 000417 0x80BD4714 */ .word	0x8200001C
/* 000418 0x80BD4718 */ .word	0x00000000
glabel objHgdoorOverlayInfoOffset
/* 000419 0x80BD471C */ .word	0x00000080
