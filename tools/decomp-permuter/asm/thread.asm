.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osDequeueThread
/* 009460 0x80089430 00803025 */ move	$a2, $a0
/* 009461 0x80089434 8CC70000 */ lw	$a3, 0X0($a2)
/* 009462 0x80089438 27BDFFF8 */ addiu	$sp, $sp, -0X8
/* 009463 0x8008943C 10E0000A */ beqz	$a3, .L80089468
/* 009464 0x80089440 00000000 */ nop
.L80089444:
/* 009465 0x80089444 14E50004 */ bne	$a3, $a1, .L80089458
/* 009466 0x80089448 00000000 */ nop
/* 009467 0x8008944C 8CAE0000 */ lw	$t6, 0X0($a1)
/* 009468 0x80089450 10000005 */ b	.L80089468
/* 009469 0x80089454 ACCE0000 */ sw	$t6, 0X0($a2)
.L80089458:
/* 009470 0x80089458 00E03025 */ move	$a2, $a3
/* 009471 0x8008945C 8CC70000 */ lw	$a3, 0X0($a2)
/* 009472 0x80089460 14E0FFF8 */ bnez	$a3, .L80089444
/* 009473 0x80089464 00000000 */ nop
.L80089468:
/* 009474 0x80089468 03E00008 */ jr	$ra
/* 009475 0x8008946C 27BD0008 */ addiu	$sp, $sp, 0X8
