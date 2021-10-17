.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osViSetMode
/* 011644 0x8008B650 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 011645 0x8008B654 AFBF0014 */ sw	$ra, 0X14($sp)
/* 011646 0x8008B658 0C024698 */ jal	__osDisableInt
/* 011647 0x8008B65C AFA40018 */ sw	$a0, 0X18($sp)
/* 011648 0x8008B660 3C05800A */ lui	$a1, %hi(__osViNext)
/* 011649 0x8008B664 24A580C4 */ addiu	$a1, $a1, %lo(__osViNext)
/* 011650 0x8008B668 8CAF0000 */ lw	$t7, 0X0($a1)
/* 011651 0x8008B66C 8FAE0018 */ lw	$t6, 0X18($sp)
/* 011652 0x8008B670 24180001 */ li	$t8, 0X1
/* 011653 0x8008B674 00402025 */ move	$a0, $v0
/* 011654 0x8008B678 ADEE0008 */ sw	$t6, 0X8($t7)
/* 011655 0x8008B67C 8CB90000 */ lw	$t9, 0X0($a1)
/* 011656 0x8008B680 A7380000 */ sh	$t8, 0X0($t9)
/* 011657 0x8008B684 8CA30000 */ lw	$v1, 0X0($a1)
/* 011658 0x8008B688 8C680008 */ lw	$t0, 0X8($v1)
/* 011659 0x8008B68C 8D090004 */ lw	$t1, 0X4($t0)
/* 011660 0x8008B690 0C0246B4 */ jal	__osRestoreInt
/* 011661 0x8008B694 AC69000C */ sw	$t1, 0XC($v1)
/* 011662 0x8008B698 8FBF0014 */ lw	$ra, 0X14($sp)
/* 011663 0x8008B69C 27BD0018 */ addiu	$sp, $sp, 0X18
/* 011664 0x8008B6A0 03E00008 */ jr	$ra
/* 011665 0x8008B6A4 00000000 */ nop
/* 011666 0x8008B6A8 00000000 */ nop
/* 011667 0x8008B6AC 00000000 */ nop
