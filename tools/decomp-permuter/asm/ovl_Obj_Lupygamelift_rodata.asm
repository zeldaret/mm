.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objLupygameliftOverlayInfo
/* 000388 0x80AF0780 */ .word	0x000005B0
/* 000389 0x80AF0784 */ .word	0x00000050
/* 000390 0x80AF0788 */ .word	0x00000010
/* 000391 0x80AF078C */ .word	0x00000000
/* 000392 0x80AF0790 */ .word	0x0000001F
glabel objLupygameliftOverlayRelocations
/* 000393 0x80AF0794 */ .word	0x4500001C
/* 000394 0x80AF0798 */ .word	0x46000020
/* 000395 0x80AF079C */ .word	0x4500002C
/* 000396 0x80AF07A0 */ .word	0x46000030
/* 000397 0x80AF07A4 */ .word	0x450000AC
/* 000398 0x80AF07A8 */ .word	0x460000B0
/* 000399 0x80AF07AC */ .word	0x440001D0
/* 000400 0x80AF07B0 */ .word	0x45000224
/* 000401 0x80AF07B4 */ .word	0x4600022C
/* 000402 0x80AF07B8 */ .word	0x45000234
/* 000403 0x80AF07BC */ .word	0x46000254
/* 000404 0x80AF07C0 */ .word	0x45000280
/* 000405 0x80AF07C4 */ .word	0x46000284
/* 000406 0x80AF07C8 */ .word	0x45000288
/* 000407 0x80AF07CC */ .word	0x4600028C
/* 000408 0x80AF07D0 */ .word	0x45000290
/* 000409 0x80AF07D4 */ .word	0x46000294
/* 000410 0x80AF07D8 */ .word	0x45000328
/* 000411 0x80AF07DC */ .word	0x46000330
/* 000412 0x80AF07E0 */ .word	0x4500034C
/* 000413 0x80AF07E4 */ .word	0x46000354
/* 000414 0x80AF07E8 */ .word	0x44000380
/* 000415 0x80AF07EC */ .word	0x450003A8
/* 000416 0x80AF07F0 */ .word	0x460003AC
/* 000417 0x80AF07F4 */ .word	0x45000484
/* 000418 0x80AF07F8 */ .word	0x46000488
/* 000419 0x80AF07FC */ .word	0x44000540
/* 000420 0x80AF0800 */ .word	0x82000010
/* 000421 0x80AF0804 */ .word	0x82000014
/* 000422 0x80AF0808 */ .word	0x82000018
/* 000423 0x80AF080C */ .word	0x8200001C
/* 000424 0x80AF0810 */ .word	0x00000000
/* 000425 0x80AF0814 */ .word	0x00000000
/* 000426 0x80AF0818 */ .word	0x00000000
glabel objLupygameliftOverlayInfoOffset
/* 000427 0x80AF081C */ .word	0x000000A0
