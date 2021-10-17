.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .rodata

glabel enDnhOverlayInfo
/* 000456 0x80A51460 */ .word	0x00000510
/* 000457 0x80A51464 */ .word	0x00000200
/* 000458 0x80A51468 */ .word	0x00000010
/* 000459 0x80A5146C */ .word	0x00000000
/* 000460 0x80A51470 */ .word	0x0000001D
glabel enDnhOverlayRelocations
/* 000461 0x80A51474 */ .word	0x450000DC
/* 000462 0x80A51478 */ .word	0x460000E4
/* 000463 0x80A5147C */ .word	0x450000E8
/* 000464 0x80A51480 */ .word	0x460000F0
/* 000465 0x80A51484 */ .word	0x450000D8
/* 000466 0x80A51488 */ .word	0x460000F4
/* 000467 0x80A5148C */ .word	0x44000150
/* 000468 0x80A51490 */ .word	0x45000158
/* 000469 0x80A51494 */ .word	0x46000160
/* 000470 0x80A51498 */ .word	0x45000234
/* 000471 0x80A5149C */ .word	0x46000238
/* 000472 0x80A514A0 */ .word	0x450002CC
/* 000473 0x80A514A4 */ .word	0x460002D0
/* 000474 0x80A514A8 */ .word	0x450002E0
/* 000475 0x80A514AC */ .word	0x460002E4
/* 000476 0x80A514B0 */ .word	0x45000354
/* 000477 0x80A514B4 */ .word	0x46000358
/* 000478 0x80A514B8 */ .word	0x45000364
/* 000479 0x80A514BC */ .word	0x4600036C
/* 000480 0x80A514C0 */ .word	0x440003B8
/* 000481 0x80A514C4 */ .word	0x440003D4
/* 000482 0x80A514C8 */ .word	0x450004B8
/* 000483 0x80A514CC */ .word	0x460004CC
/* 000484 0x80A514D0 */ .word	0x450004D8
/* 000485 0x80A514D4 */ .word	0x460004F8
/* 000486 0x80A514D8 */ .word	0x820001CC
/* 000487 0x80A514DC */ .word	0x820001D0
/* 000488 0x80A514E0 */ .word	0x820001D4
/* 000489 0x80A514E4 */ .word	0x820001D8
/* 000490 0x80A514E8 */ .word	0x00000000
glabel enDnhOverlayInfoOffset
/* 000491 0x80A514EC */ .word	0x00000090
