.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel kanfontOrdering
/* 286748 0x801BDB30 */ .word	0x10111213
/* 286749 0x801BDB34 */ .word	0x14151617
/* 286750 0x801BDB38 */ .word	0x18192122
/* 286751 0x801BDB3C */ .word	0x23242526
/* 286752 0x801BDB40 */ .word	0x2728292A
/* 286753 0x801BDB44 */ .word	0x2B2C2D2E
/* 286754 0x801BDB48 */ .word	0x2F303132
/* 286755 0x801BDB4C */ .word	0x33343536
/* 286756 0x801BDB50 */ .word	0x3738393A
/* 286757 0x801BDB54 */ .word	0x41424344
/* 286758 0x801BDB58 */ .word	0x45464748
/* 286759 0x801BDB5C */ .word	0x494A4B4C
/* 286760 0x801BDB60 */ .word	0x4D4E4F50
/* 286761 0x801BDB64 */ .word	0x51525354
/* 286762 0x801BDB68 */ .word	0x55565758
/* 286763 0x801BDB6C */ .word	0x595A000D
/* 286764 0x801BDB70 */ .word	0x0E1A6166
/* 286765 0x801BDB74 */ .word	0x6A6D6F73
/* 286766 0x801BDB78 */ .word	0x76777879
/* 286767 0x801BDB7C */ .word	0x7A7B7C7D
/* 286768 0x801BDB80 */ .word	0x7E7F8081
/* 286769 0x801BDB84 */ .word	0x84868788
/* 286770 0x801BDB88 */ .word	0x898A8B8C
/* 286771 0x801BDB8C */ .word	0x00000000
