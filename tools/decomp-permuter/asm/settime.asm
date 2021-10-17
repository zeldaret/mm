.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osSetTime
/* 018572 0x80092290 AFA40000 */ sw	$a0, 0X0($sp)
/* 018573 0x80092294 8FAE0000 */ lw	$t6, 0X0($sp)
/* 018574 0x80092298 AFA50004 */ sw	$a1, 0X4($sp)
/* 018575 0x8009229C 3C01800A */ lui	$at, %hi(__osCurrentTime)
/* 018576 0x800922A0 8FAF0004 */ lw	$t7, 0X4($sp)
/* 018577 0x800922A4 AC2EE5B0 */ sw	$t6, %lo(__osCurrentTime)($at)
/* 018578 0x800922A8 3C01800A */ lui	$at, %hi(__osCurrentTime + 0x4)
/* 018579 0x800922AC 03E00008 */ jr	$ra
/* 018580 0x800922B0 AC2FE5B4 */ sw	$t7, %lo(__osCurrentTime + 0x4)($at)
/* 018581 0x800922B4 00000000 */ nop
/* 018582 0x800922B8 00000000 */ nop
/* 018583 0x800922BC 00000000 */ nop
