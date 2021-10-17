.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osSetGlobalIntMask
/* 016776 0x80090680 27BDFFD8 */ addiu	$sp, $sp, -0X28
/* 016777 0x80090684 AFBF001C */ sw	$ra, 0X1C($sp)
/* 016778 0x80090688 AFA40028 */ sw	$a0, 0X28($sp)
/* 016779 0x8009068C 0C024698 */ jal	__osDisableInt
/* 016780 0x80090690 AFB00018 */ sw	$s0, 0X18($sp)
/* 016781 0x80090694 3C0E8009 */ lui	$t6, %hi(__OSGlobalIntMask)
/* 016782 0x80090698 8DCE7E60 */ lw	$t6, %lo(__OSGlobalIntMask)($t6)
/* 016783 0x8009069C 8FAF0028 */ lw	$t7, 0X28($sp)
/* 016784 0x800906A0 00408025 */ move	$s0, $v0
/* 016785 0x800906A4 3C018009 */ lui	$at, %hi(__OSGlobalIntMask)
/* 016786 0x800906A8 01CFC025 */ or	$t8, $t6, $t7
/* 016787 0x800906AC AC387E60 */ sw	$t8, %lo(__OSGlobalIntMask)($at)
/* 016788 0x800906B0 0C0246B4 */ jal	__osRestoreInt
/* 016789 0x800906B4 02002025 */ move	$a0, $s0
/* 016790 0x800906B8 8FBF001C */ lw	$ra, 0X1C($sp)
/* 016791 0x800906BC 8FB00018 */ lw	$s0, 0X18($sp)
/* 016792 0x800906C0 27BD0028 */ addiu	$sp, $sp, 0X28
/* 016793 0x800906C4 03E00008 */ jr	$ra
/* 016794 0x800906C8 00000000 */ nop
/* 016795 0x800906CC 00000000 */ nop
