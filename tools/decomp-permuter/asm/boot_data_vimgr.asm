.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel __osViDevMgr
/* 024640 0x80098160 */ .word	0x00000000
/* 024641 0x80098164 */ .word	0x00000000
/* 024642 0x80098168 */ .word	0x00000000
/* 024643 0x8009816C */ .word	0x00000000
/* 024644 0x80098170 */ .word	0x00000000
/* 024645 0x80098174 */ .word	0x00000000
/* 024646 0x80098178 */ .word	0x00000000
glabel D_8009817C
/* 024647 0x8009817C */ .word	0x00000000
glabel D_80098180
/* 024648 0x80098180 */ .word	0x008040C0
/* 024649 0x80098184 */ .word	0x20A060E0
/* 024650 0x80098188 */ .word	0x00000000
/* 024651 0x8009818C */ .word	0x00000000
