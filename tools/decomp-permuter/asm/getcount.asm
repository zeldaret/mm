.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osGetCount
/* 013464 0x8008D2C0 40024800 */ mfc0	$v0, $9
/* 013465 0x8008D2C4 03E00008 */ jr	$ra
/* 013466 0x8008D2C8 00000000 */ nop
/* 013467 0x8008D2CC 00000000 */ nop
/* 013468 0x8008D2D0 00000000 */ nop
/* 013469 0x8008D2D4 00000000 */ nop
/* 013470 0x8008D2D8 00000000 */ nop
/* 013471 0x8008D2DC 00000000 */ nop
