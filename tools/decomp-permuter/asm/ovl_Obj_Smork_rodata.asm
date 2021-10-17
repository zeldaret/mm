.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel objSmorkOverlayInfo
/* 000804 0x80A3E310 */ .word	0x00000BF0
/* 000805 0x80A3E314 */ .word	0x00000090
/* 000806 0x80A3E318 */ .word	0x00000010
/* 000807 0x80A3E31C */ .word	0x00000000
/* 000808 0x80A3E320 */ .word	0x00000017
glabel objSmorkOverlayRelocations
/* 000809 0x80A3E324 */ .word	0x440002D0
/* 000810 0x80A3E328 */ .word	0x45000364
/* 000811 0x80A3E32C */ .word	0x46000368
/* 000812 0x80A3E330 */ .word	0x45000370
/* 000813 0x80A3E334 */ .word	0x4600038C
/* 000814 0x80A3E338 */ .word	0x45000394
/* 000815 0x80A3E33C */ .word	0x46000500
/* 000816 0x80A3E340 */ .word	0x45000430
/* 000817 0x80A3E344 */ .word	0x460005AC
/* 000818 0x80A3E348 */ .word	0x450004BC
/* 000819 0x80A3E34C */ .word	0x46000658
/* 000820 0x80A3E350 */ .word	0x450004B0
/* 000821 0x80A3E354 */ .word	0x460004B4
/* 000822 0x80A3E358 */ .word	0x45000A24
/* 000823 0x80A3E35C */ .word	0x46000A28
/* 000824 0x80A3E360 */ .word	0x45000B5C
/* 000825 0x80A3E364 */ .word	0x46000B60
/* 000826 0x80A3E368 */ .word	0x44000BB0
/* 000827 0x80A3E36C */ .word	0x44000BD0
/* 000828 0x80A3E370 */ .word	0x82000010
/* 000829 0x80A3E374 */ .word	0x82000014
/* 000830 0x80A3E378 */ .word	0x82000018
/* 000831 0x80A3E37C */ .word	0x8200001C
/* 000832 0x80A3E380 */ .word	0x00000000
/* 000833 0x80A3E384 */ .word	0x00000000
/* 000834 0x80A3E388 */ .word	0x00000000
glabel objSmorkOverlayInfoOffset
/* 000835 0x80A3E38C */ .word	0x00000080
