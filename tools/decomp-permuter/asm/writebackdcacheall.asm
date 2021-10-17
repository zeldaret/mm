.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osWritebackDCacheAll
/* 021848 0x800955C0 3C088000 */ lui	$t0, 0x8000
/* 021849 0x800955C4 240A2000 */ li	$t2, 0X2000
/* 021850 0x800955C8 010A4821 */ addu	$t1, $t0, $t2
/* 021851 0x800955CC 2529FFF0 */ addiu	$t1, $t1, -0X10
.L800955D0:
/* 021852 0x800955D0 BD010000 */ cache	0x01, 0X0($t0)
/* 021853 0x800955D4 0109082B */ sltu	$at, $t0, $t1
/* 021854 0x800955D8 1420FFFD */ bnez	$at, .L800955D0
/* 021855 0x800955DC 25080010 */ addiu	$t0, $t0, 0X10
/* 021856 0x800955E0 03E00008 */ jr	$ra
/* 021857 0x800955E4 00000000 */ nop
/* 021858 0x800955E8 00000000 */ nop
/* 021859 0x800955EC 00000000 */ nop
