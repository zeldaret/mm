.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel func_800920B0
/* 018452 0x800920B0 27BDFFE0 */ addiu	$sp, $sp, -0X20
/* 018453 0x800920B4 AFBF0014 */ sw	$ra, 0X14($sp)
/* 018454 0x800920B8 AFA40020 */ sw	$a0, 0X20($sp)
/* 018455 0x800920BC AFA50024 */ sw	$a1, 0X24($sp)
/* 018456 0x800920C0 0C023078 */ jal	__osPiGetAccess
/* 018457 0x800920C4 AFA60028 */ sw	$a2, 0X28($sp)
/* 018458 0x800920C8 8FA40020 */ lw	$a0, 0X20($sp)
/* 018459 0x800920CC 8FA50024 */ lw	$a1, 0X24($sp)
/* 018460 0x800920D0 0C023F40 */ jal	func_8008FD00
/* 018461 0x800920D4 8FA60028 */ lw	$a2, 0X28($sp)
/* 018462 0x800920D8 0C023089 */ jal	__osPiRelAccess
/* 018463 0x800920DC AFA2001C */ sw	$v0, 0X1C($sp)
/* 018464 0x800920E0 8FBF0014 */ lw	$ra, 0X14($sp)
/* 018465 0x800920E4 8FA2001C */ lw	$v0, 0X1C($sp)
/* 018466 0x800920E8 27BD0020 */ addiu	$sp, $sp, 0X20
/* 018467 0x800920EC 03E00008 */ jr	$ra
/* 018468 0x800920F0 00000000 */ nop
/* 018469 0x800920F4 00000000 */ nop
/* 018470 0x800920F8 00000000 */ nop
/* 018471 0x800920FC 00000000 */ nop
