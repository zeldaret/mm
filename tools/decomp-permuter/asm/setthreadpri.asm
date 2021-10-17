.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osSetThreadPri
/* 016104 0x8008FC00 27BDFFD8 */ addiu	$sp, $sp, -0X28
/* 016105 0x8008FC04 AFBF001C */ sw	$ra, 0X1C($sp)
/* 016106 0x8008FC08 AFA40028 */ sw	$a0, 0X28($sp)
/* 016107 0x8008FC0C AFA5002C */ sw	$a1, 0X2C($sp)
/* 016108 0x8008FC10 0C024698 */ jal	__osDisableInt
/* 016109 0x8008FC14 AFB00018 */ sw	$s0, 0X18($sp)
/* 016110 0x8008FC18 8FAE0028 */ lw	$t6, 0X28($sp)
/* 016111 0x8008FC1C 00408025 */ move	$s0, $v0
/* 016112 0x8008FC20 15C00004 */ bnez	$t6, .L8008FC34
/* 016113 0x8008FC24 00000000 */ nop
/* 016114 0x8008FC28 3C0F8009 */ lui	$t7, %hi(__osRunningThread)
/* 016115 0x8008FC2C 8DEF7E20 */ lw	$t7, %lo(__osRunningThread)($t7)
/* 016116 0x8008FC30 AFAF0028 */ sw	$t7, 0X28($sp)
.L8008FC34:
/* 016117 0x8008FC34 8FB80028 */ lw	$t8, 0X28($sp)
/* 016118 0x8008FC38 8FA8002C */ lw	$t0, 0X2C($sp)
/* 016119 0x8008FC3C 8F190004 */ lw	$t9, 0X4($t8)
/* 016120 0x8008FC40 13280020 */ beq	$t9, $t0, .L8008FCC4
/* 016121 0x8008FC44 00000000 */ nop
/* 016122 0x8008FC48 AF080004 */ sw	$t0, 0X4($t8)
/* 016123 0x8008FC4C 3C0A8009 */ lui	$t2, %hi(__osRunningThread)
/* 016124 0x8008FC50 8D4A7E20 */ lw	$t2, %lo(__osRunningThread)($t2)
/* 016125 0x8008FC54 8FA90028 */ lw	$t1, 0X28($sp)
/* 016126 0x8008FC58 112A000C */ beq	$t1, $t2, .L8008FC8C
/* 016127 0x8008FC5C 00000000 */ nop
/* 016128 0x8008FC60 952B0010 */ lhu	$t3, 0X10($t1)
/* 016129 0x8008FC64 24010001 */ li	$at, 0X1
/* 016130 0x8008FC68 11610008 */ beq	$t3, $at, .L8008FC8C
/* 016131 0x8008FC6C 00000000 */ nop
/* 016132 0x8008FC70 8D240008 */ lw	$a0, 0X8($t1)
/* 016133 0x8008FC74 0C02250C */ jal	__osDequeueThread
/* 016134 0x8008FC78 01202825 */ move	$a1, $t1
/* 016135 0x8008FC7C 8FAC0028 */ lw	$t4, 0X28($sp)
/* 016136 0x8008FC80 8D840008 */ lw	$a0, 0X8($t4)
/* 016137 0x8008FC84 0C022491 */ jal	__osEnqueueThread
/* 016138 0x8008FC88 01802825 */ move	$a1, $t4
.L8008FC8C:
/* 016139 0x8008FC8C 3C0D8009 */ lui	$t5, %hi(__osRunningThread)
/* 016140 0x8008FC90 3C0F8009 */ lui	$t7, %hi(__osRunQueue)
/* 016141 0x8008FC94 8DEF7E18 */ lw	$t7, %lo(__osRunQueue)($t7)
/* 016142 0x8008FC98 8DAD7E20 */ lw	$t5, %lo(__osRunningThread)($t5)
/* 016143 0x8008FC9C 8DF90004 */ lw	$t9, 0X4($t7)
/* 016144 0x8008FCA0 8DAE0004 */ lw	$t6, 0X4($t5)
/* 016145 0x8008FCA4 01D9082A */ slt	$at, $t6, $t9
/* 016146 0x8008FCA8 10200006 */ beqz	$at, .L8008FCC4
/* 016147 0x8008FCAC 00000000 */ nop
/* 016148 0x8008FCB0 24080002 */ li	$t0, 0X2
/* 016149 0x8008FCB4 3C048009 */ lui	$a0, %hi(__osRunQueue)
/* 016150 0x8008FCB8 A5A80010 */ sh	$t0, 0X10($t5)
/* 016151 0x8008FCBC 0C022451 */ jal	__osEnqueueAndYield
/* 016152 0x8008FCC0 24847E18 */ addiu	$a0, $a0, %lo(__osRunQueue)
.L8008FCC4:
/* 016153 0x8008FCC4 0C0246B4 */ jal	__osRestoreInt
/* 016154 0x8008FCC8 02002025 */ move	$a0, $s0
/* 016155 0x8008FCCC 8FBF001C */ lw	$ra, 0X1C($sp)
/* 016156 0x8008FCD0 8FB00018 */ lw	$s0, 0X18($sp)
/* 016157 0x8008FCD4 27BD0028 */ addiu	$sp, $sp, 0X28
/* 016158 0x8008FCD8 03E00008 */ jr	$ra
/* 016159 0x8008FCDC 00000000 */ nop
