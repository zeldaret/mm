.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel proutSprintf
/* 007668 0x80087830 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 007669 0x80087834 AFBF0014 */ sw	$ra, 0X14($sp)
/* 007670 0x80087838 0C023C82 */ jal	memcpy
/* 007671 0x8008783C AFA60020 */ sw	$a2, 0X20($sp)
/* 007672 0x80087840 8FBF0014 */ lw	$ra, 0X14($sp)
/* 007673 0x80087844 8FAE0020 */ lw	$t6, 0X20($sp)
/* 007674 0x80087848 27BD0018 */ addiu	$sp, $sp, 0X18
/* 007675 0x8008784C 03E00008 */ jr	$ra
/* 007676 0x80087850 004E1021 */ addu	$v0, $v0, $t6

glabel vsprintf
/* 007677 0x80087854 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 007678 0x80087858 AFA40018 */ sw	$a0, 0X18($sp)
/* 007679 0x8008785C 00C03825 */ move	$a3, $a2
/* 007680 0x80087860 00A03025 */ move	$a2, $a1
/* 007681 0x80087864 AFBF0014 */ sw	$ra, 0X14($sp)
/* 007682 0x80087868 AFA5001C */ sw	$a1, 0X1C($sp)
/* 007683 0x8008786C 3C048008 */ lui	$a0, %hi(proutSprintf)
/* 007684 0x80087870 24847830 */ addiu	$a0, $a0, %lo(proutSprintf)
/* 007685 0x80087874 0C023814 */ jal	_Printf
/* 007686 0x80087878 8FA50018 */ lw	$a1, 0X18($sp)
/* 007687 0x8008787C 04400004 */ bltz	$v0, .L80087890
/* 007688 0x80087880 00401825 */ move	$v1, $v0
/* 007689 0x80087884 8FAE0018 */ lw	$t6, 0X18($sp)
/* 007690 0x80087888 01C27821 */ addu	$t7, $t6, $v0
/* 007691 0x8008788C A1E00000 */ sb	$zero, 0X0($t7)
.L80087890:
/* 007692 0x80087890 8FBF0014 */ lw	$ra, 0X14($sp)
/* 007693 0x80087894 27BD0018 */ addiu	$sp, $sp, 0X18
/* 007694 0x80087898 00601025 */ move	$v0, $v1
/* 007695 0x8008789C 03E00008 */ jr	$ra
/* 007696 0x800878A0 00000000 */ nop

glabel sprintf
/* 007697 0x800878A4 27BDFFE0 */ addiu	$sp, $sp, -0X20
/* 007698 0x800878A8 AFA40020 */ sw	$a0, 0X20($sp)
/* 007699 0x800878AC AFBF0014 */ sw	$ra, 0X14($sp)
/* 007700 0x800878B0 AFA50024 */ sw	$a1, 0X24($sp)
/* 007701 0x800878B4 AFA60028 */ sw	$a2, 0X28($sp)
/* 007702 0x800878B8 AFA7002C */ sw	$a3, 0X2C($sp)
/* 007703 0x800878BC 3C048008 */ lui	$a0, %hi(proutSprintf)
/* 007704 0x800878C0 24847830 */ addiu	$a0, $a0, %lo(proutSprintf)
/* 007705 0x800878C4 27A70028 */ addiu	$a3, $sp, 0X28
/* 007706 0x800878C8 8FA60024 */ lw	$a2, 0X24($sp)
/* 007707 0x800878CC 0C023814 */ jal	_Printf
/* 007708 0x800878D0 8FA50020 */ lw	$a1, 0X20($sp)
/* 007709 0x800878D4 04400004 */ bltz	$v0, .L800878E8
/* 007710 0x800878D8 00401825 */ move	$v1, $v0
/* 007711 0x800878DC 8FAE0020 */ lw	$t6, 0X20($sp)
/* 007712 0x800878E0 01C27821 */ addu	$t7, $t6, $v0
/* 007713 0x800878E4 A1E00000 */ sb	$zero, 0X0($t7)
.L800878E8:
/* 007714 0x800878E8 8FBF0014 */ lw	$ra, 0X14($sp)
/* 007715 0x800878EC 27BD0020 */ addiu	$sp, $sp, 0X20
/* 007716 0x800878F0 00601025 */ move	$v0, $v1
/* 007717 0x800878F4 03E00008 */ jr	$ra
/* 007718 0x800878F8 00000000 */ nop
/* 007719 0x800878FC 00000000 */ nop
