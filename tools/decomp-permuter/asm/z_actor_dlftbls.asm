.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel ActorOverlayTable_FaultPrint
/* 026552 0x800BF9A0 27BDFFD0 */ addiu	$sp, $sp, -0X30
/* 026553 0x800BF9A4 AFBF002C */ sw	$ra, 0X2C($sp)
/* 026554 0x800BF9A8 AFB30028 */ sw	$s3, 0X28($sp)
/* 026555 0x800BF9AC AFB20024 */ sw	$s2, 0X24($sp)
/* 026556 0x800BF9B0 AFB10020 */ sw	$s1, 0X20($sp)
/* 026557 0x800BF9B4 AFB0001C */ sw	$s0, 0X1C($sp)
/* 026558 0x800BF9B8 AFA40030 */ sw	$a0, 0X30($sp)
/* 026559 0x800BF9BC AFA50034 */ sw	$a1, 0X34($sp)
/* 026560 0x800BF9C0 2404FFFE */ li	$a0, -0X2
/* 026561 0x800BF9C4 0C0210E7 */ jal	FaultDrawer_SetCharPad
/* 026562 0x800BF9C8 00002825 */ move	$a1, $zero
/* 026563 0x800BF9CC 3C12801B */ lui	$s2, %hi(gMaxActorId)
/* 026564 0x800BF9D0 26524610 */ addiu	$s2, $s2, %lo(gMaxActorId)
/* 026565 0x800BF9D4 3C04801E */ lui	$a0, %hi(D_801DCBB0)
/* 026566 0x800BF9D8 2484CBB0 */ addiu	$a0, $a0, %lo(D_801DCBB0)
/* 026567 0x800BF9DC 0C0211F3 */ jal	FaultDrawer_Printf
/* 026568 0x800BF9E0 8E450000 */ lw	$a1, 0X0($s2)
/* 026569 0x800BF9E4 3C04801E */ lui	$a0, %hi(D_801DCBC4)
/* 026570 0x800BF9E8 0C0211F3 */ jal	FaultDrawer_Printf
/* 026571 0x800BF9EC 2484CBC4 */ addiu	$a0, $a0, %lo(D_801DCBC4)
/* 026572 0x800BF9F0 8E420000 */ lw	$v0, 0X0($s2)
/* 026573 0x800BF9F4 3C10801B */ lui	$s0, %hi(gActorOverlayTable)
/* 026574 0x800BF9F8 2610EFD0 */ addiu	$s0, $s0, %lo(gActorOverlayTable)
/* 026575 0x800BF9FC 18400017 */ blez	$v0, .L800BFA5C
/* 026576 0x800BFA00 00008825 */ move	$s1, $zero
/* 026577 0x800BFA04 3C13801E */ lui	$s3, %hi(D_801DCBFC)
/* 026578 0x800BFA08 3C12801E */ lui	$s2, %hi(D_801DCBE4)
/* 026579 0x800BFA0C 2652CBE4 */ addiu	$s2, $s2, %lo(D_801DCBE4)
/* 026580 0x800BFA10 2673CBFC */ addiu	$s3, $s3, %lo(D_801DCBFC)
.L800BFA14:
/* 026581 0x800BFA14 8E060010 */ lw	$a2, 0X10($s0)
/* 026582 0x800BFA18 8E0E000C */ lw	$t6, 0XC($s0)
/* 026583 0x800BFA1C 8E0F0008 */ lw	$t7, 0X8($s0)
/* 026584 0x800BFA20 02402025 */ move	$a0, $s2
/* 026585 0x800BFA24 10C00009 */ beqz	$a2, .L800BFA4C
/* 026586 0x800BFA28 01CF1823 */ subu	$v1, $t6, $t7
/* 026587 0x800BFA2C 8218001E */ lb	$t8, 0X1E($s0)
/* 026588 0x800BFA30 AFB30014 */ sw	$s3, 0X14($sp)
/* 026589 0x800BFA34 02202825 */ move	$a1, $s1
/* 026590 0x800BFA38 00C33821 */ addu	$a3, $a2, $v1
/* 026591 0x800BFA3C 0C0211F3 */ jal	FaultDrawer_Printf
/* 026592 0x800BFA40 AFB80010 */ sw	$t8, 0X10($sp)
/* 026593 0x800BFA44 3C02801B */ lui	$v0, %hi(gMaxActorId)
/* 026594 0x800BFA48 8C424610 */ lw	$v0, %lo(gMaxActorId)($v0)
.L800BFA4C:
/* 026595 0x800BFA4C 26310001 */ addiu	$s1, $s1, 0X1
/* 026596 0x800BFA50 0222082A */ slt	$at, $s1, $v0
/* 026597 0x800BFA54 1420FFEF */ bnez	$at, .L800BFA14
/* 026598 0x800BFA58 26100020 */ addiu	$s0, $s0, 0X20
.L800BFA5C:
/* 026599 0x800BFA5C 8FBF002C */ lw	$ra, 0X2C($sp)
/* 026600 0x800BFA60 8FB0001C */ lw	$s0, 0X1C($sp)
/* 026601 0x800BFA64 8FB10020 */ lw	$s1, 0X20($sp)
/* 026602 0x800BFA68 8FB20024 */ lw	$s2, 0X24($sp)
/* 026603 0x800BFA6C 8FB30028 */ lw	$s3, 0X28($sp)
/* 026604 0x800BFA70 03E00008 */ jr	$ra
/* 026605 0x800BFA74 27BD0030 */ addiu	$sp, $sp, 0X30

glabel ActorOverlayTable_FaultAddrConv
/* 026606 0x800BFA78 AFA50004 */ sw	$a1, 0X4($sp)
/* 026607 0x800BFA7C 3C05801B */ lui	$a1, %hi(gMaxActorId)
/* 026608 0x800BFA80 8CA54610 */ lw	$a1, %lo(gMaxActorId)($a1)
/* 026609 0x800BFA84 3C02801B */ lui	$v0, %hi(gActorOverlayTable)
/* 026610 0x800BFA88 2442EFD0 */ addiu	$v0, $v0, %lo(gActorOverlayTable)
/* 026611 0x800BFA8C 18A00013 */ blez	$a1, .L800BFADC
/* 026612 0x800BFA90 00001825 */ move	$v1, $zero
.L800BFA94:
/* 026613 0x800BFA94 8C480010 */ lw	$t0, 0X10($v0)
/* 026614 0x800BFA98 8C470008 */ lw	$a3, 0X8($v0)
/* 026615 0x800BFA9C 8C4E000C */ lw	$t6, 0XC($v0)
/* 026616 0x800BFAA0 0088082B */ sltu	$at, $a0, $t0
/* 026617 0x800BFAA4 00E84823 */ subu	$t1, $a3, $t0
/* 026618 0x800BFAA8 11000008 */ beqz	$t0, .L800BFACC
/* 026619 0x800BFAAC 01C73023 */ subu	$a2, $t6, $a3
/* 026620 0x800BFAB0 14200006 */ bnez	$at, .L800BFACC
/* 026621 0x800BFAB4 01067821 */ addu	$t7, $t0, $a2
/* 026622 0x800BFAB8 008F082B */ sltu	$at, $a0, $t7
/* 026623 0x800BFABC 50200004 */ beqzl	$at, .L800BFAD0
/* 026624 0x800BFAC0 24630001 */ addiu	$v1, $v1, 0X1
/* 026625 0x800BFAC4 03E00008 */ jr	$ra
/* 026626 0x800BFAC8 00891021 */ addu	$v0, $a0, $t1
.L800BFACC:
/* 026627 0x800BFACC 24630001 */ addiu	$v1, $v1, 0X1
.L800BFAD0:
/* 026628 0x800BFAD0 0065082A */ slt	$at, $v1, $a1
/* 026629 0x800BFAD4 1420FFEF */ bnez	$at, .L800BFA94
/* 026630 0x800BFAD8 24420020 */ addiu	$v0, $v0, 0X20
.L800BFADC:
/* 026631 0x800BFADC 00001025 */ move	$v0, $zero
/* 026632 0x800BFAE0 03E00008 */ jr	$ra
/* 026633 0x800BFAE4 00000000 */ nop

glabel ActorOverlayTable_Init
/* 026634 0x800BFAE8 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 026635 0x800BFAEC AFBF0014 */ sw	$ra, 0X14($sp)
/* 026636 0x800BFAF0 240E02B2 */ li	$t6, 0X2B2
/* 026637 0x800BFAF4 3C01801B */ lui	$at, %hi(gMaxActorId)
/* 026638 0x800BFAF8 3C04801F */ lui	$a0, %hi(D_801ED930)
/* 026639 0x800BFAFC 3C05800C */ lui	$a1, %hi(ActorOverlayTable_FaultPrint)
/* 026640 0x800BFB00 AC2E4610 */ sw	$t6, %lo(gMaxActorId)($at)
/* 026641 0x800BFB04 24A5F9A0 */ addiu	$a1, $a1, %lo(ActorOverlayTable_FaultPrint)
/* 026642 0x800BFB08 2484D930 */ addiu	$a0, $a0, %lo(D_801ED930)
/* 026643 0x800BFB0C 00003025 */ move	$a2, $zero
/* 026644 0x800BFB10 0C02067C */ jal	Fault_AddClient
/* 026645 0x800BFB14 00003825 */ move	$a3, $zero
/* 026646 0x800BFB18 3C04801F */ lui	$a0, %hi(D_801ED940)
/* 026647 0x800BFB1C 3C05800C */ lui	$a1, %hi(ActorOverlayTable_FaultAddrConv)
/* 026648 0x800BFB20 24A5FA78 */ addiu	$a1, $a1, %lo(ActorOverlayTable_FaultAddrConv)
/* 026649 0x800BFB24 2484D940 */ addiu	$a0, $a0, %lo(D_801ED940)
/* 026650 0x800BFB28 0C0206F3 */ jal	Fault_AddAddrConvClient
/* 026651 0x800BFB2C 00003025 */ move	$a2, $zero
/* 026652 0x800BFB30 8FBF0014 */ lw	$ra, 0X14($sp)
/* 026653 0x800BFB34 27BD0018 */ addiu	$sp, $sp, 0X18
/* 026654 0x800BFB38 03E00008 */ jr	$ra
/* 026655 0x800BFB3C 00000000 */ nop

glabel ActorOverlayTable_Cleanup
/* 026656 0x800BFB40 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 026657 0x800BFB44 AFBF0014 */ sw	$ra, 0X14($sp)
/* 026658 0x800BFB48 3C04801F */ lui	$a0, %hi(D_801ED930)
/* 026659 0x800BFB4C 0C0206B5 */ jal	Fault_RemoveClient
/* 026660 0x800BFB50 2484D930 */ addiu	$a0, $a0, %lo(D_801ED930)
/* 026661 0x800BFB54 3C04801F */ lui	$a0, %hi(D_801ED940)
/* 026662 0x800BFB58 0C020729 */ jal	Fault_RemoveAddrConvClient
/* 026663 0x800BFB5C 2484D940 */ addiu	$a0, $a0, %lo(D_801ED940)
/* 026664 0x800BFB60 3C01801B */ lui	$at, %hi(gMaxActorId)
/* 026665 0x800BFB64 AC204610 */ sw	$zero, %lo(gMaxActorId)($at)
/* 026666 0x800BFB68 8FBF0014 */ lw	$ra, 0X14($sp)
/* 026667 0x800BFB6C 27BD0018 */ addiu	$sp, $sp, 0X18
/* 026668 0x800BFB70 03E00008 */ jr	$ra
/* 026669 0x800BFB74 00000000 */ nop
/* 026670 0x800BFB78 00000000 */ nop
/* 026671 0x800BFB7C 00000000 */ nop
