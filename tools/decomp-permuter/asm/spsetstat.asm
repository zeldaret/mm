.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osSpSetStatus
/* 021640 0x80095280 3C0EA404 */ lui	$t6, 0xA404
/* 021641 0x80095284 03E00008 */ jr	$ra
/* 021642 0x80095288 ADC40010 */ sw	$a0, 0X10($t6)
/* 021643 0x8009528C 00000000 */ nop
/* 021644 0x80095290 00000000 */ nop
/* 021645 0x80095294 00000000 */ nop
/* 021646 0x80095298 00000000 */ nop
/* 021647 0x8009529C 00000000 */ nop
