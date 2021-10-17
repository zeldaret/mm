.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osSpTaskYielded
/* 016528 0x800902A0 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 016529 0x800902A4 AFBF0014 */ sw	$ra, 0X14($sp)
/* 016530 0x800902A8 0C02549C */ jal	__osSpGetStatus
/* 016531 0x800902AC AFA40018 */ sw	$a0, 0X18($sp)
/* 016532 0x800902B0 304E0100 */ andi	$t6, $v0, 0X100
/* 016533 0x800902B4 11C00003 */ beqz	$t6, .L800902C4
/* 016534 0x800902B8 8FA40018 */ lw	$a0, 0X18($sp)
/* 016535 0x800902BC 10000002 */ b	.L800902C8
/* 016536 0x800902C0 24030001 */ li	$v1, 0X1
.L800902C4:
/* 016537 0x800902C4 00001825 */ move	$v1, $zero
.L800902C8:
/* 016538 0x800902C8 304F0080 */ andi	$t7, $v0, 0X80
/* 016539 0x800902CC 51E00008 */ beqzl	$t7, .L800902F0
/* 016540 0x800902D0 8FBF0014 */ lw	$ra, 0X14($sp)
/* 016541 0x800902D4 8C980004 */ lw	$t8, 0X4($a0)
/* 016542 0x800902D8 2401FFFD */ li	$at, -0X3
/* 016543 0x800902DC 0303C825 */ or	$t9, $t8, $v1
/* 016544 0x800902E0 AC990004 */ sw	$t9, 0X4($a0)
/* 016545 0x800902E4 03214824 */ and	$t1, $t9, $at
/* 016546 0x800902E8 AC890004 */ sw	$t1, 0X4($a0)
/* 016547 0x800902EC 8FBF0014 */ lw	$ra, 0X14($sp)
.L800902F0:
/* 016548 0x800902F0 27BD0018 */ addiu	$sp, $sp, 0X18
/* 016549 0x800902F4 00601025 */ move	$v0, $v1
/* 016550 0x800902F8 03E00008 */ jr	$ra
/* 016551 0x800902FC 00000000 */ nop
