.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel func_80172BC0
/* 209984 0x80172BC0 27BDFFD8 */ addiu	$sp, $sp, -0X28
/* 209985 0x80172BC4 AFBF0024 */ sw	$ra, 0X24($sp)
/* 209986 0x80172BC8 AFB20020 */ sw	$s2, 0X20($sp)
/* 209987 0x80172BCC AFB1001C */ sw	$s1, 0X1C($sp)
/* 209988 0x80172BD0 AFB00018 */ sw	$s0, 0X18($sp)
/* 209989 0x80172BD4 3C10801E */ lui	$s0, %hi(D_801DFC70)
/* 209990 0x80172BD8 3C12801E */ lui	$s2, %hi(D_801DFC77)
/* 209991 0x80172BDC 2652FC77 */ addiu	$s2, $s2, %lo(D_801DFC77)
/* 209992 0x80172BE0 2610FC70 */ addiu	$s0, $s0, %lo(D_801DFC70)
/* 209993 0x80172BE4 24110004 */ li	$s1, 0X4
/* 209994 0x80172BE8 920E0000 */ lbu	$t6, 0X0($s0)
.L80172BEC:
/* 209995 0x80172BEC 522E0004 */ beql	$s1, $t6, .L80172C00
/* 209996 0x80172BF0 26100001 */ addiu	$s0, $s0, 0X1
/* 209997 0x80172BF4 0C069C21 */ jal	func_801A7084
/* 209998 0x80172BF8 92040000 */ lbu	$a0, 0X0($s0)
/* 209999 0x80172BFC 26100001 */ addiu	$s0, $s0, 0X1
.L80172C00:
/* 210000 0x80172C00 0212082B */ sltu	$at, $s0, $s2
/* 210001 0x80172C04 5420FFF9 */ bnezl	$at, .L80172BEC
/* 210002 0x80172C08 920E0000 */ lbu	$t6, 0X0($s0)
/* 210003 0x80172C0C 8FBF0024 */ lw	$ra, 0X24($sp)
/* 210004 0x80172C10 8FB00018 */ lw	$s0, 0X18($sp)
/* 210005 0x80172C14 8FB1001C */ lw	$s1, 0X1C($sp)
/* 210006 0x80172C18 8FB20020 */ lw	$s2, 0X20($sp)
/* 210007 0x80172C1C 03E00008 */ jr	$ra
/* 210008 0x80172C20 27BD0028 */ addiu	$sp, $sp, 0X28
/* 210009 0x80172C24 00000000 */ nop
/* 210010 0x80172C28 00000000 */ nop
/* 210011 0x80172C2C 00000000 */ nop
