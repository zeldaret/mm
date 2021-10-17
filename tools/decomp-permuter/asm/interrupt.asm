.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osDisableInt
/* 018048 0x80091A60 3C0A8009 */ lui	$t2, %hi(__OSGlobalIntMask)
/* 018049 0x80091A64 254A7E60 */ addiu	$t2, $t2, %lo(__OSGlobalIntMask)
/* 018050 0x80091A68 8D4B0000 */ lw	$t3, 0X0($t2)
/* 018051 0x80091A6C 316BFF00 */ andi	$t3, $t3, 0XFF00
/* 018052 0x80091A70 40086000 */ mfc0	$t0, $12
/* 018053 0x80091A74 2401FFFE */ li	$at, -0X2
/* 018054 0x80091A78 01014824 */ and	$t1, $t0, $at
/* 018055 0x80091A7C 40896000 */ mtc0	$t1, $12
/* 018056 0x80091A80 31020001 */ andi	$v0, $t0, 0X1
/* 018057 0x80091A84 8D480000 */ lw	$t0, 0X0($t2)
/* 018058 0x80091A88 3108FF00 */ andi	$t0, $t0, 0XFF00
/* 018059 0x80091A8C 110B000E */ beq	$t0, $t3, .L80091AC8
/* 018060 0x80091A90 3C0A8009 */ lui	$t2, %hi(__osRunningThread)
/* 018061 0x80091A94 254A7E20 */ addiu	$t2, $t2, %lo(__osRunningThread)
/* 018062 0x80091A98 8D490118 */ lw	$t1, 0X118($t2)
/* 018063 0x80091A9C 312AFF00 */ andi	$t2, $t1, 0XFF00
/* 018064 0x80091AA0 01485024 */ and	$t2, $t2, $t0
/* 018065 0x80091AA4 3C01FFFF */ lui	$at, 0xFFFF
/* 018066 0x80091AA8 342100FF */ ori	$at, $at, 0XFF
/* 018067 0x80091AAC 01214824 */ and	$t1, $t1, $at
/* 018068 0x80091AB0 012A4825 */ or	$t1, $t1, $t2
/* 018069 0x80091AB4 2401FFFE */ li	$at, -0X2
/* 018070 0x80091AB8 01214824 */ and	$t1, $t1, $at
/* 018071 0x80091ABC 40896000 */ mtc0	$t1, $12
/* 018072 0x80091AC0 00000000 */ nop
/* 018073 0x80091AC4 00000000 */ nop
.L80091AC8:
/* 018074 0x80091AC8 03E00008 */ jr	$ra
/* 018075 0x80091ACC 00000000 */ nop

glabel __osRestoreInt
/* 018076 0x80091AD0 40086000 */ mfc0	$t0, $12
/* 018077 0x80091AD4 01044025 */ or	$t0, $t0, $a0
/* 018078 0x80091AD8 40886000 */ mtc0	$t0, $12
/* 018079 0x80091ADC 00000000 */ nop
/* 018080 0x80091AE0 00000000 */ nop
/* 018081 0x80091AE4 03E00008 */ jr	$ra
/* 018082 0x80091AE8 00000000 */ nop
/* 018083 0x80091AEC 00000000 */ nop
