.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osVirtualToPhysical
/* 010552 0x8008A540 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 010553 0x8008A544 AFA40018 */ sw	$a0, 0X18($sp)
/* 010554 0x8008A548 8FAE0018 */ lw	$t6, 0X18($sp)
/* 010555 0x8008A54C 3C018000 */ lui	$at, 0x8000
/* 010556 0x8008A550 AFBF0014 */ sw	$ra, 0X14($sp)
/* 010557 0x8008A554 01C1082B */ sltu	$at, $t6, $at
/* 010558 0x8008A558 14200007 */ bnez	$at, .L8008A578
/* 010559 0x8008A55C 3C01A000 */ lui	$at, 0xA000
/* 010560 0x8008A560 01C1082B */ sltu	$at, $t6, $at
/* 010561 0x8008A564 10200004 */ beqz	$at, .L8008A578
/* 010562 0x8008A568 3C011FFF */ lui	$at, 0x1FFF
/* 010563 0x8008A56C 3421FFFF */ ori	$at, $at, 0XFFFF
/* 010564 0x8008A570 1000000E */ b	.L8008A5AC
/* 010565 0x8008A574 01C11024 */ and	$v0, $t6, $at
.L8008A578:
/* 010566 0x8008A578 8FAF0018 */ lw	$t7, 0X18($sp)
/* 010567 0x8008A57C 3C01A000 */ lui	$at, 0xA000
/* 010568 0x8008A580 01E1082B */ sltu	$at, $t7, $at
/* 010569 0x8008A584 14200007 */ bnez	$at, .L8008A5A4
/* 010570 0x8008A588 3C01C000 */ lui	$at, 0xC000
/* 010571 0x8008A58C 01E1082B */ sltu	$at, $t7, $at
/* 010572 0x8008A590 10200004 */ beqz	$at, .L8008A5A4
/* 010573 0x8008A594 3C011FFF */ lui	$at, 0x1FFF
/* 010574 0x8008A598 3421FFFF */ ori	$at, $at, 0XFFFF
/* 010575 0x8008A59C 10000003 */ b	.L8008A5AC
/* 010576 0x8008A5A0 01E11024 */ and	$v0, $t7, $at
.L8008A5A4:
/* 010577 0x8008A5A4 0C022FD8 */ jal	__osProbeTLB
/* 010578 0x8008A5A8 8FA40018 */ lw	$a0, 0X18($sp)
.L8008A5AC:
/* 010579 0x8008A5AC 8FBF0014 */ lw	$ra, 0X14($sp)
/* 010580 0x8008A5B0 27BD0018 */ addiu	$sp, $sp, 0X18
/* 010581 0x8008A5B4 03E00008 */ jr	$ra
/* 010582 0x8008A5B8 00000000 */ nop
/* 010583 0x8008A5BC 00000000 */ nop
