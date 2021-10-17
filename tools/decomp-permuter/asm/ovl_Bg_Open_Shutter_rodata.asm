.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel bgOpenShutterOverlayInfo
/* 000404 0x80ACB160 */ .word	0x00000610
/* 000405 0x80ACB164 */ .word	0x00000030
/* 000406 0x80ACB168 */ .word	0x00000010
/* 000407 0x80ACB16C */ .word	0x00000000
/* 000408 0x80ACB170 */ .word	0x0000001A
glabel bgOpenShutterOverlayRelocations
/* 000409 0x80ACB174 */ .word	0x4500005C
/* 000410 0x80ACB178 */ .word	0x4600008C
/* 000411 0x80ACB17C */ .word	0x440000EC
/* 000412 0x80ACB180 */ .word	0x450001C8
/* 000413 0x80ACB184 */ .word	0x460001CC
/* 000414 0x80ACB188 */ .word	0x450001FC
/* 000415 0x80ACB18C */ .word	0x46000200
/* 000416 0x80ACB190 */ .word	0x450002EC
/* 000417 0x80ACB194 */ .word	0x460002F0
/* 000418 0x80ACB198 */ .word	0x44000310
/* 000419 0x80ACB19C */ .word	0x450003C0
/* 000420 0x80ACB1A0 */ .word	0x460003C4
/* 000421 0x80ACB1A4 */ .word	0x450004D0
/* 000422 0x80ACB1A8 */ .word	0x460004D4
/* 000423 0x80ACB1AC */ .word	0x45000548
/* 000424 0x80ACB1B0 */ .word	0x4600054C
/* 000425 0x80ACB1B4 */ .word	0x45000564
/* 000426 0x80ACB1B8 */ .word	0x46000568
/* 000427 0x80ACB1BC */ .word	0x4500058C
/* 000428 0x80ACB1C0 */ .word	0x46000590
/* 000429 0x80ACB1C4 */ .word	0x450005A4
/* 000430 0x80ACB1C8 */ .word	0x460005A8
/* 000431 0x80ACB1CC */ .word	0x82000010
/* 000432 0x80ACB1D0 */ .word	0x82000014
/* 000433 0x80ACB1D4 */ .word	0x82000018
/* 000434 0x80ACB1D8 */ .word	0x8200001C
glabel bgOpenShutterOverlayInfoOffset
/* 000435 0x80ACB1DC */ .word	0x00000080
