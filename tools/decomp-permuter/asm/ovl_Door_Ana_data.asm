.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel Door_Ana_InitVars
/* 000360 0x808E0740 */ .word	0x00550700
/* 000361 0x808E0744 */ .word	0x02000000
/* 000362 0x808E0748 */ .word	0x00020000
/* 000363 0x808E074C */ .word	0x00000194
/* 000364 0x808E0750 */ .word	DoorAna_Init
/* 000365 0x808E0754 */ .word	DoorAna_Destroy
/* 000366 0x808E0758 */ .word	DoorAna_Update
/* 000367 0x808E075C */ .word	DoorAna_Draw
glabel D_808E0760
/* 000368 0x808E0760 */ .word	0x0A000900
/* 000369 0x808E0764 */ .word	0x00010000
/* 000370 0x808E0768 */ .word	0x02000000
/* 000371 0x808E076C */ .word	0x00000000
/* 000372 0x808E0770 */ .word	0x00000000
/* 000373 0x808E0774 */ .word	0x00000008
/* 000374 0x808E0778 */ .word	0x00000000
/* 000375 0x808E077C */ .word	0x00010000
/* 000376 0x808E0780 */ .word	0x0032000A
/* 000377 0x808E0784 */ .word	0x00000000
/* 000378 0x808E0788 */ .word	0x00000000
glabel D_808E078C
/* 000379 0x808E078C */ .word	0x1A001400
/* 000380 0x808E0790 */ .word	0x14101420
/* 000381 0x808E0794 */ .word	0x14301440
/* 000382 0x808E0798 */ .word	0x14501460
/* 000383 0x808E079C */ .word	0x14701480
/* 000384 0x808E07A0 */ .word	0x149014A0
/* 000385 0x808E07A4 */ .word	0x14B014C0
/* 000386 0x808E07A8 */ .word	0x14D00000
/* 000387 0x808E07AC */ .word	0x00000000
