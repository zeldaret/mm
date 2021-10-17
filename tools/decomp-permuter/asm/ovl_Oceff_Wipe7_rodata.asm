.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel oceffWipe7OverlayInfo
/* 000884 0x80BCEA80 */ .word	0x00000310
/* 000885 0x80BCEA84 */ .word	0x00000AB0
/* 000886 0x80BCEA88 */ .word	0x00000010
/* 000887 0x80BCEA8C */ .word	0x00000010
/* 000888 0x80BCEA90 */ .word	0x0000001B
glabel oceffWipe7OverlayRelocations
/* 000889 0x80BCEA94 */ .word	0x4500016C
/* 000890 0x80BCEA98 */ .word	0x46000170
/* 000891 0x80BCEA9C */ .word	0x45000188
/* 000892 0x80BCEAA0 */ .word	0x4600018C
/* 000893 0x80BCEAA4 */ .word	0x450001C4
/* 000894 0x80BCEAA8 */ .word	0x460001C8
/* 000895 0x80BCEAAC */ .word	0x450001CC
/* 000896 0x80BCEAB0 */ .word	0x460001D0
/* 000897 0x80BCEAB4 */ .word	0x450001D4
/* 000898 0x80BCEAB8 */ .word	0x460001E0
/* 000899 0x80BCEABC */ .word	0x4500019C
/* 000900 0x80BCEAC0 */ .word	0x460001E4
/* 000901 0x80BCEAC4 */ .word	0x450001D8
/* 000902 0x80BCEAC8 */ .word	0x460001DC
/* 000903 0x80BCEACC */ .word	0x45000240
/* 000904 0x80BCEAD0 */ .word	0x46000244
/* 000905 0x80BCEAD4 */ .word	0x450002C4
/* 000906 0x80BCEAD8 */ .word	0x460002D0
/* 000907 0x80BCEADC */ .word	0x450002D8
/* 000908 0x80BCEAE0 */ .word	0x460002DC
/* 000909 0x80BCEAE4 */ .word	0x82000010
/* 000910 0x80BCEAE8 */ .word	0x82000014
/* 000911 0x80BCEAEC */ .word	0x82000018
/* 000912 0x80BCEAF0 */ .word	0x8200001C
/* 000913 0x80BCEAF4 */ .word	0x8200082C
/* 000914 0x80BCEAF8 */ .word	0x82000A04
/* 000915 0x80BCEAFC */ .word	0x82000A4C
/* 000916 0x80BCEB00 */ .word	0x00000000
/* 000917 0x80BCEB04 */ .word	0x00000000
/* 000918 0x80BCEB08 */ .word	0x00000000
glabel oceffWipe7OverlayInfoOffset
/* 000919 0x80BCEB0C */ .word	0x00000090
