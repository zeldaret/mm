.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel D_80098210
/* 024684 0x80098210 */ .word	0xB0B5BDCC
/* 024685 0x80098214 */ .word	0xC5B8B3AB
/* 024686 0x80098218 */ .word	0xB0DBBEEF
/* 024687 0x8009821C */ .word	0x0A000000
glabel yaz0String80098220
/* 024688 0x80098220 */ .word	0x736C6964
/* 024689 0x80098224 */ .word	0x6D612073
/* 024690 0x80098228 */ .word	0x6C696473
/* 024691 0x8009822C */ .word	0x74617274
/* 024692 0x80098230 */ .word	0x5F737A73
/* 024693 0x80098234 */ .word	0x20726574
/* 024694 0x80098238 */ .word	0x3D256400
glabel yaz0String8009823C
/* 024695 0x8009823C */ .word	0x7372633A
/* 024696 0x80098240 */ .word	0x2530386C
/* 024697 0x80098244 */ .word	0x78206473
/* 024698 0x80098248 */ .word	0x743A2530
/* 024699 0x8009824C */ .word	0x386C7820
/* 024700 0x80098250 */ .word	0x73697A3A
/* 024701 0x80098254 */ .word	0x2530386C
/* 024702 0x80098258 */ .word	0x78000000
/* 024703 0x8009825C */ .word	0x00000000
