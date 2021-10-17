.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osGetTime
/* 016624 0x80090420 27BDFFC8 */ addiu	$sp, $sp, -0X38
/* 016625 0x80090424 AFBF001C */ sw	$ra, 0X1C($sp)
/* 016626 0x80090428 0C024698 */ jal	__osDisableInt
/* 016627 0x8009042C AFB00018 */ sw	$s0, 0X18($sp)
/* 016628 0x80090430 0C0234B0 */ jal	osGetCount
/* 016629 0x80090434 00408025 */ move	$s0, $v0
/* 016630 0x80090438 AFA20034 */ sw	$v0, 0X34($sp)
/* 016631 0x8009043C 3C0F800A */ lui	$t7, %hi(__osBaseCounter)
/* 016632 0x80090440 8DEFE5B8 */ lw	$t7, %lo(__osBaseCounter)($t7)
/* 016633 0x80090444 8FAE0034 */ lw	$t6, 0X34($sp)
/* 016634 0x80090448 3C08800A */ lui	$t0, %hi(__osCurrentTime)
/* 016635 0x8009044C 3C09800A */ lui	$t1, %hi(__osCurrentTime + 0x4)
/* 016636 0x80090450 8D29E5B4 */ lw	$t1, %lo(__osCurrentTime + 0x4)($t1)
/* 016637 0x80090454 8D08E5B0 */ lw	$t0, %lo(__osCurrentTime)($t0)
/* 016638 0x80090458 01CFC023 */ subu	$t8, $t6, $t7
/* 016639 0x8009045C AFB80030 */ sw	$t8, 0X30($sp)
/* 016640 0x80090460 02002025 */ move	$a0, $s0
/* 016641 0x80090464 AFA9002C */ sw	$t1, 0X2C($sp)
/* 016642 0x80090468 0C0246B4 */ jal	__osRestoreInt
/* 016643 0x8009046C AFA80028 */ sw	$t0, 0X28($sp)
/* 016644 0x80090470 8FB90030 */ lw	$t9, 0X30($sp)
/* 016645 0x80090474 8FAD002C */ lw	$t5, 0X2C($sp)
/* 016646 0x80090478 8FBF001C */ lw	$ra, 0X1C($sp)
/* 016647 0x8009047C 03205825 */ move	$t3, $t9
/* 016648 0x80090480 016D1821 */ addu	$v1, $t3, $t5
/* 016649 0x80090484 8FAC0028 */ lw	$t4, 0X28($sp)
/* 016650 0x80090488 240A0000 */ li	$t2, 0X0
/* 016651 0x8009048C 006D082B */ sltu	$at, $v1, $t5
/* 016652 0x80090490 002A1021 */ addu	$v0, $at, $t2
/* 016653 0x80090494 8FB00018 */ lw	$s0, 0X18($sp)
/* 016654 0x80090498 27BD0038 */ addiu	$sp, $sp, 0X38
/* 016655 0x8009049C 03E00008 */ jr	$ra
/* 016656 0x800904A0 004C1021 */ addu	$v0, $v0, $t4
/* 016657 0x800904A4 00000000 */ nop
/* 016658 0x800904A8 00000000 */ nop
/* 016659 0x800904AC 00000000 */ nop
