.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osYieldThread
/* 020224 0x80093C60 27BDFFD8 */ addiu	$sp, $sp, -0X28
/* 020225 0x80093C64 AFBF001C */ sw	$ra, 0X1C($sp)
/* 020226 0x80093C68 0C024698 */ jal	__osDisableInt
/* 020227 0x80093C6C AFB00018 */ sw	$s0, 0X18($sp)
/* 020228 0x80093C70 3C0F8009 */ lui	$t7, %hi(__osRunningThread)
/* 020229 0x80093C74 8DEF7E20 */ lw	$t7, %lo(__osRunningThread)($t7)
/* 020230 0x80093C78 240E0002 */ li	$t6, 0X2
/* 020231 0x80093C7C 3C048009 */ lui	$a0, %hi(__osRunQueue)
/* 020232 0x80093C80 00408025 */ move	$s0, $v0
/* 020233 0x80093C84 24847E18 */ addiu	$a0, $a0, %lo(__osRunQueue)
/* 020234 0x80093C88 0C022451 */ jal	__osEnqueueAndYield
/* 020235 0x80093C8C A5EE0010 */ sh	$t6, 0X10($t7)
/* 020236 0x80093C90 0C0246B4 */ jal	__osRestoreInt
/* 020237 0x80093C94 02002025 */ move	$a0, $s0
/* 020238 0x80093C98 8FBF001C */ lw	$ra, 0X1C($sp)
/* 020239 0x80093C9C 8FB00018 */ lw	$s0, 0X18($sp)
/* 020240 0x80093CA0 27BD0028 */ addiu	$sp, $sp, 0X28
/* 020241 0x80093CA4 03E00008 */ jr	$ra
/* 020242 0x80093CA8 00000000 */ nop
/* 020243 0x80093CAC 00000000 */ nop
/* 020244 0x80093CB0 00000000 */ nop
/* 020245 0x80093CB4 00000000 */ nop
/* 020246 0x80093CB8 00000000 */ nop
/* 020247 0x80093CBC 00000000 */ nop
