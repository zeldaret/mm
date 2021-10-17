.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osResetGlobalIntMask
/* 017756 0x800915D0 27BDFFD8 */ addiu	$sp, $sp, -0X28
/* 017757 0x800915D4 AFBF001C */ sw	$ra, 0X1C($sp)
/* 017758 0x800915D8 AFA40028 */ sw	$a0, 0X28($sp)
/* 017759 0x800915DC 0C024698 */ jal	__osDisableInt
/* 017760 0x800915E0 AFB00018 */ sw	$s0, 0X18($sp)
/* 017761 0x800915E4 8FAF0028 */ lw	$t7, 0X28($sp)
/* 017762 0x800915E8 3C0E8009 */ lui	$t6, %hi(__OSGlobalIntMask)
/* 017763 0x800915EC 8DCE7E60 */ lw	$t6, %lo(__OSGlobalIntMask)($t6)
/* 017764 0x800915F0 2401FBFE */ li	$at, -0X402
/* 017765 0x800915F4 01E1C024 */ and	$t8, $t7, $at
/* 017766 0x800915F8 0300C827 */ nor	$t9, $t8, $zero
/* 017767 0x800915FC 00408025 */ move	$s0, $v0
/* 017768 0x80091600 3C018009 */ lui	$at, %hi(__OSGlobalIntMask)
/* 017769 0x80091604 01D94024 */ and	$t0, $t6, $t9
/* 017770 0x80091608 AC287E60 */ sw	$t0, %lo(__OSGlobalIntMask)($at)
/* 017771 0x8009160C 0C0246B4 */ jal	__osRestoreInt
/* 017772 0x80091610 02002025 */ move	$a0, $s0
/* 017773 0x80091614 8FBF001C */ lw	$ra, 0X1C($sp)
/* 017774 0x80091618 8FB00018 */ lw	$s0, 0X18($sp)
/* 017775 0x8009161C 27BD0028 */ addiu	$sp, $sp, 0X28
/* 017776 0x80091620 03E00008 */ jr	$ra
/* 017777 0x80091624 00000000 */ nop
/* 017778 0x80091628 00000000 */ nop
/* 017779 0x8009162C 00000000 */ nop
