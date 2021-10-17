.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enMFire1OverlayInfo
/* 000088 0x808B5390 */ .word	0x00000110
/* 000089 0x808B5394 */ .word	0x00000050
/* 000090 0x808B5398 */ .word	0x00000000
/* 000091 0x808B539C */ .word	0x00000000
/* 000092 0x808B53A0 */ .word	0x00000005
glabel enMFire1OverlayRelocations
/* 000093 0x808B53A4 */ .word	0x45000024
/* 000094 0x808B53A8 */ .word	0x46000030
/* 000095 0x808B53AC */ .word	0x82000010
/* 000096 0x808B53B0 */ .word	0x82000014
/* 000097 0x808B53B4 */ .word	0x82000018
/* 000098 0x808B53B8 */ .word	0x00000000
glabel enMFire1OverlayInfoOffset
/* 000099 0x808B53BC */ .word	0x00000030
