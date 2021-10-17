.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osContStartQuery
/* 013748 0x8008D730 27BDFFE0 */ addiu	$sp, $sp, -0X20
/* 013749 0x8008D734 AFBF0014 */ sw	$ra, 0X14($sp)
/* 013750 0x8008D738 0C0226BC */ jal	__osSiGetAccess
/* 013751 0x8008D73C AFA40020 */ sw	$a0, 0X20($sp)
/* 013752 0x8008D740 3C0E800A */ lui	$t6, %hi(__osContLastCmd)
/* 013753 0x8008D744 91CECF10 */ lbu	$t6, %lo(__osContLastCmd)($t6)
/* 013754 0x8008D748 11C0000B */ beqz	$t6, .L8008D778
/* 013755 0x8008D74C 00000000 */ nop
/* 013756 0x8008D750 0C02275A */ jal	__osPackRequestData
/* 013757 0x8008D754 00002025 */ move	$a0, $zero
/* 013758 0x8008D758 3C05800A */ lui	$a1, %hi(__osContPifRam)
/* 013759 0x8008D75C 24A5CED0 */ addiu	$a1, $a1, %lo(__osContPifRam)
/* 013760 0x8008D760 0C022B5C */ jal	__osSiRawStartDma
/* 013761 0x8008D764 24040001 */ li	$a0, 0X1
/* 013762 0x8008D768 8FA40020 */ lw	$a0, 0X20($sp)
/* 013763 0x8008D76C 00002825 */ move	$a1, $zero
/* 013764 0x8008D770 0C021FB4 */ jal	osRecvMesg
/* 013765 0x8008D774 24060001 */ li	$a2, 0X1
.L8008D778:
/* 013766 0x8008D778 3C05800A */ lui	$a1, %hi(__osContPifRam)
/* 013767 0x8008D77C 24A5CED0 */ addiu	$a1, $a1, %lo(__osContPifRam)
/* 013768 0x8008D780 0C022B5C */ jal	__osSiRawStartDma
/* 013769 0x8008D784 00002025 */ move	$a0, $zero
/* 013770 0x8008D788 3C01800A */ lui	$at, %hi(__osContLastCmd)
/* 013771 0x8008D78C AFA2001C */ sw	$v0, 0X1C($sp)
/* 013772 0x8008D790 0C0226CD */ jal	__osSiRelAccess
/* 013773 0x8008D794 A020CF10 */ sb	$zero, %lo(__osContLastCmd)($at)
/* 013774 0x8008D798 8FBF0014 */ lw	$ra, 0X14($sp)
/* 013775 0x8008D79C 8FA2001C */ lw	$v0, 0X1C($sp)
/* 013776 0x8008D7A0 27BD0020 */ addiu	$sp, $sp, 0X20
/* 013777 0x8008D7A4 03E00008 */ jr	$ra
/* 013778 0x8008D7A8 00000000 */ nop

glabel osContGetQuery
/* 013779 0x8008D7AC 27BDFFE0 */ addiu	$sp, $sp, -0X20
/* 013780 0x8008D7B0 AFBF0014 */ sw	$ra, 0X14($sp)
/* 013781 0x8008D7B4 00802825 */ move	$a1, $a0
/* 013782 0x8008D7B8 0C02272F */ jal	__osContGetInitData
/* 013783 0x8008D7BC 27A4001F */ addiu	$a0, $sp, 0X1F
/* 013784 0x8008D7C0 8FBF0014 */ lw	$ra, 0X14($sp)
/* 013785 0x8008D7C4 27BD0020 */ addiu	$sp, $sp, 0X20
/* 013786 0x8008D7C8 03E00008 */ jr	$ra
/* 013787 0x8008D7CC 00000000 */ nop
