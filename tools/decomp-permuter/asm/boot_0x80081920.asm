.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel Fault_Nop80081920
/* 001584 0x80081920 27BDFFF8 */ addiu	$sp, $sp, -0X8
/* 001585 0x80081924 AFA40008 */ sw	$a0, 0X8($sp)
/* 001586 0x80081928 AFA5000C */ sw	$a1, 0XC($sp)
/* 001587 0x8008192C AFA60010 */ sw	$a2, 0X10($sp)
/* 001588 0x80081930 AFA70014 */ sw	$a3, 0X14($sp)
/* 001589 0x80081934 03E00008 */ jr	$ra
/* 001590 0x80081938 27BD0008 */ addiu	$sp, $sp, 0X8

glabel Fault_Log
/* 001591 0x8008193C 27BDFFF8 */ addiu	$sp, $sp, -0X8
/* 001592 0x80081940 AFA40008 */ sw	$a0, 0X8($sp)
/* 001593 0x80081944 AFA5000C */ sw	$a1, 0XC($sp)
/* 001594 0x80081948 AFA60010 */ sw	$a2, 0X10($sp)
/* 001595 0x8008194C AFA70014 */ sw	$a3, 0X14($sp)
/* 001596 0x80081950 03E00008 */ jr	$ra
/* 001597 0x80081954 27BD0008 */ addiu	$sp, $sp, 0X8

glabel Fault_Nop80081958
/* 001598 0x80081958 27BDFFF8 */ addiu	$sp, $sp, -0X8
/* 001599 0x8008195C AFA40008 */ sw	$a0, 0X8($sp)
/* 001600 0x80081960 AFA5000C */ sw	$a1, 0XC($sp)
/* 001601 0x80081964 AFA60010 */ sw	$a2, 0X10($sp)
/* 001602 0x80081968 AFA70014 */ sw	$a3, 0X14($sp)
/* 001603 0x8008196C 03E00008 */ jr	$ra
/* 001604 0x80081970 27BD0008 */ addiu	$sp, $sp, 0X8
/* 001605 0x80081974 00000000 */ nop
/* 001606 0x80081978 00000000 */ nop
/* 001607 0x8008197C 00000000 */ nop
