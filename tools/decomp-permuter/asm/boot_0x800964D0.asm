.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel func_800964D0
/* 022812 0x800964D0 27BDFFE0 */ addiu	$sp, $sp, -0X20
/* 022813 0x800964D4 AFBF0014 */ sw	$ra, 0X14($sp)
/* 022814 0x800964D8 0C024698 */ jal	__osDisableInt
/* 022815 0x800964DC 00000000 */ nop
/* 022816 0x800964E0 3C0E800A */ lui	$t6, %hi(__osViCurr)
/* 022817 0x800964E4 8DCE80C0 */ lw	$t6, %lo(__osViCurr)($t6)
/* 022818 0x800964E8 00402025 */ move	$a0, $v0
/* 022819 0x800964EC 8DCF0004 */ lw	$t7, 0X4($t6)
/* 022820 0x800964F0 0C0246B4 */ jal	__osRestoreInt
/* 022821 0x800964F4 AFAF0018 */ sw	$t7, 0X18($sp)
/* 022822 0x800964F8 8FBF0014 */ lw	$ra, 0X14($sp)
/* 022823 0x800964FC 8FA20018 */ lw	$v0, 0X18($sp)
/* 022824 0x80096500 27BD0020 */ addiu	$sp, $sp, 0X20
/* 022825 0x80096504 03E00008 */ jr	$ra
/* 022826 0x80096508 00000000 */ nop
/* 022827 0x8009650C 00000000 */ nop
