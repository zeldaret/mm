.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel doorAnaOverlayInfo
/* 000392 0x808E07C0 */ .word	0x000005A0
/* 000393 0x808E07C4 */ .word	0x00000070
/* 000394 0x808E07C8 */ .word	0x00000010
/* 000395 0x808E07CC */ .word	0x00000000
/* 000396 0x808E07D0 */ .word	0x00000016
glabel doorAnaOverlayRelocations
/* 000397 0x808E07D4 */ .word	0x45000054
/* 000398 0x808E07D8 */ .word	0x46000058
/* 000399 0x808E07DC */ .word	0x45000088
/* 000400 0x808E07E0 */ .word	0x4600008C
/* 000401 0x808E07E4 */ .word	0x44000090
/* 000402 0x808E07E8 */ .word	0x450000A0
/* 000403 0x808E07EC */ .word	0x460000A8
/* 000404 0x808E07F0 */ .word	0x440000A4
/* 000405 0x808E07F4 */ .word	0x4500012C
/* 000406 0x808E07F8 */ .word	0x46000130
/* 000407 0x808E07FC */ .word	0x450001DC
/* 000408 0x808E0800 */ .word	0x460001E0
/* 000409 0x808E0804 */ .word	0x440001E8
/* 000410 0x808E0808 */ .word	0x45000334
/* 000411 0x808E080C */ .word	0x46000350
/* 000412 0x808E0810 */ .word	0x45000360
/* 000413 0x808E0814 */ .word	0x46000364
/* 000414 0x808E0818 */ .word	0x44000368
/* 000415 0x808E081C */ .word	0x82000010
/* 000416 0x808E0820 */ .word	0x82000014
/* 000417 0x808E0824 */ .word	0x82000018
/* 000418 0x808E0828 */ .word	0x8200001C
glabel doorAnaOverlayInfoOffset
/* 000419 0x808E082C */ .word	0x00000070
