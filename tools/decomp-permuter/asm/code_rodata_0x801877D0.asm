.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel jtbl_D_801E0280
/* 322032 0x801E0280 */ .word	L80189A88
/* 322033 0x801E0284 */ .word	L80189AC4
/* 322034 0x801E0288 */ .word	L80189B54
/* 322035 0x801E028C */ .word	L80189A9C
/* 322036 0x801E0290 */ .word	L80189AD8
/* 322037 0x801E0294 */ .word	L80189B84
/* 322038 0x801E0298 */ .word	L80189B54
/* 322039 0x801E029C */ .word	L80189AB0
glabel D_801E02A0
/* 322040 0x801E02A0 */ .word	0x46FFFE00
/* 322041 0x801E02A4 */ .word	0x00000000
/* 322042 0x801E02A8 */ .word	0x00000000
/* 322043 0x801E02AC */ .word	0x00000000
