.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel bootproc
/* 000000 0x80080060 27BDFFE0 */ addiu	$sp, $sp, -0X20
/* 000001 0x80080064 AFBF001C */ sw	$ra, 0X1C($sp)
/* 000002 0x80080068 3C0F800A */ lui	$t7, %hi(bootThreadName)
/* 000003 0x8008006C 25EF8190 */ addiu	$t7, $t7, %lo(bootThreadName)
/* 000004 0x80080070 3C04800A */ lui	$a0, %hi(sBootThreadInfo)
/* 000005 0x80080074 3C05800A */ lui	$a1, %hi(sBootThreadStack)
/* 000006 0x80080078 3C06800A */ lui	$a2, %hi(irqmgrContext)
/* 000007 0x8008007C 240EFFFF */ li	$t6, -0X1
/* 000008 0x80080080 AFAE0010 */ sw	$t6, 0X10($sp)
/* 000009 0x80080084 24C69EF0 */ addiu	$a2, $a2, %lo(irqmgrContext)
/* 000010 0x80080088 24A59AF0 */ addiu	$a1, $a1, %lo(sBootThreadStack)
/* 000011 0x8008008C 24849500 */ addiu	$a0, $a0, %lo(sBootThreadInfo)
/* 000012 0x80080090 AFAF0014 */ sw	$t7, 0X14($sp)
/* 000013 0x80080094 0C0214C8 */ jal	StackCheck_Init
/* 000014 0x80080098 00003825 */ move	$a3, $zero
/* 000015 0x8008009C 0C0234D4 */ jal	osGetMemSize
/* 000016 0x800800A0 00000000 */ nop
/* 000017 0x800800A4 3C018000 */ lui	$at, %hi(osMemSize)
/* 000018 0x800800A8 0C02063D */ jal	func_800818F4
/* 000019 0x800800AC AC220318 */ sw	$v0, %lo(osMemSize)($at)
/* 000020 0x800800B0 0C0229BF */ jal	osInitialize
/* 000021 0x800800B4 00000000 */ nop
/* 000022 0x800800B8 0C023B78 */ jal	osUnmapTLBAll
/* 000023 0x800800BC 00000000 */ nop
/* 000024 0x800800C0 0C024A48 */ jal	osCartRomInit
/* 000025 0x800800C4 00000000 */ nop
/* 000026 0x800800C8 3C19800A */ lui	$t9, %hi(idleThreadName)
/* 000027 0x800800CC 3C018009 */ lui	$at, %hi(gCartHandle)
/* 000028 0x800800D0 27398198 */ addiu	$t9, $t9, %lo(idleThreadName)
/* 000029 0x800800D4 3C04800A */ lui	$a0, %hi(sIdleThreadInfo)
/* 000030 0x800800D8 3C05800A */ lui	$a1, %hi(sIdleThreadStack)
/* 000031 0x800800DC 3C06800A */ lui	$a2, %hi(sIdleThreadInfo)
/* 000032 0x800800E0 24180100 */ li	$t8, 0X100
/* 000033 0x800800E4 AC226B40 */ sw	$v0, %lo(gCartHandle)($at)
/* 000034 0x800800E8 AFB80010 */ sw	$t8, 0X10($sp)
/* 000035 0x800800EC 24C69AD0 */ addiu	$a2, $a2, %lo(sIdleThreadInfo)
/* 000036 0x800800F0 24A596D0 */ addiu	$a1, $a1, %lo(sIdleThreadStack)
/* 000037 0x800800F4 24849AD0 */ addiu	$a0, $a0, %lo(sIdleThreadInfo)
/* 000038 0x800800F8 AFB90014 */ sw	$t9, 0X14($sp)
/* 000039 0x800800FC 0C0214C8 */ jal	StackCheck_Init
/* 000040 0x80080100 00003825 */ move	$a3, $zero
/* 000041 0x80080104 3C08800A */ lui	$t0, %hi(sIdleThreadInfo)
/* 000042 0x80080108 25089AD0 */ addiu	$t0, $t0, %lo(sIdleThreadInfo)
/* 000043 0x8008010C 3C04800A */ lui	$a0, %hi(sIdleThread)
/* 000044 0x80080110 3C068008 */ lui	$a2, %hi(Idle_ThreadEntry)
/* 000045 0x80080114 2409000C */ li	$t1, 0XC
/* 000046 0x80080118 AFA90014 */ sw	$t1, 0X14($sp)
/* 000047 0x8008011C 24C60514 */ addiu	$a2, $a2, %lo(Idle_ThreadEntry)
/* 000048 0x80080120 24849520 */ addiu	$a0, $a0, %lo(sIdleThread)
/* 000049 0x80080124 AFA80010 */ sw	$t0, 0X10($sp)
/* 000050 0x80080128 24050001 */ li	$a1, 0X1
/* 000051 0x8008012C 0C022790 */ jal	osCreateThread
/* 000052 0x80080130 00003825 */ move	$a3, $zero
/* 000053 0x80080134 3C04800A */ lui	$a0, %hi(sIdleThread)
/* 000054 0x80080138 0C0255EC */ jal	osStartThread
/* 000055 0x8008013C 24849520 */ addiu	$a0, $a0, %lo(sIdleThread)
/* 000056 0x80080140 8FBF001C */ lw	$ra, 0X1C($sp)
/* 000057 0x80080144 27BD0020 */ addiu	$sp, $sp, 0X20
/* 000058 0x80080148 03E00008 */ jr	$ra
/* 000059 0x8008014C 00000000 */ nop
