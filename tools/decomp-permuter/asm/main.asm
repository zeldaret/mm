.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel main
/* 212044 0x80174BF0 27BDFFB8 */ addiu	$sp, $sp, -0X48
/* 212045 0x80174BF4 AFBF002C */ sw	$ra, 0X2C($sp)
/* 212046 0x80174BF8 AFB30028 */ sw	$s3, 0X28($sp)
/* 212047 0x80174BFC AFB20024 */ sw	$s2, 0X24($sp)
/* 212048 0x80174C00 AFB10020 */ sw	$s1, 0X20($sp)
/* 212049 0x80174C04 AFB0001C */ sw	$s0, 0X1C($sp)
/* 212050 0x80174C08 AFA40048 */ sw	$a0, 0X48($sp)
/* 212051 0x80174C0C 240E0140 */ li	$t6, 0X140
/* 212052 0x80174C10 3C01801D */ lui	$at, %hi(gScreenWidth)
/* 212053 0x80174C14 AC2E1520 */ sw	$t6, %lo(gScreenWidth)($at)
/* 212054 0x80174C18 3C01801D */ lui	$at, %hi(gScreenHeight)
/* 212055 0x80174C1C 240F00F0 */ li	$t7, 0XF0
/* 212056 0x80174C20 0C043030 */ jal	Nmi_Init
/* 212057 0x80174C24 AC2F1524 */ sw	$t7, %lo(gScreenHeight)($at)
/* 212058 0x80174C28 0C020EF1 */ jal	Fault_Start
/* 212059 0x80174C2C 00000000 */ nop
/* 212060 0x80174C30 0C05E4A9 */ jal	Check_RegionIsSupported
/* 212061 0x80174C34 00000000 */ nop
/* 212062 0x80174C38 0C05E498 */ jal	Check_ExpansionPak
/* 212063 0x80174C3C 00000000 */ nop
/* 212064 0x80174C40 3C028038 */ lui	$v0, %hi(gSystemHeap)
/* 212065 0x80174C44 3C03801D */ lui	$v1, %hi(startHeapSize)
/* 212066 0x80174C48 244424C0 */ addiu	$a0, $v0, %lo(gSystemHeap)
/* 212067 0x80174C4C 3C188078 */ lui	$t8, 0x8078
/* 212068 0x80174C50 24631528 */ addiu	$v1, $v1, %lo(startHeapSize)
/* 212069 0x80174C54 03042823 */ subu	$a1, $t8, $a0
/* 212070 0x80174C58 0C02197E */ jal	StartHeap_Init
/* 212071 0x80174C5C AC650000 */ sw	$a1, 0X0($v1)
/* 212072 0x80174C60 0C03A4F8 */ jal	static_context_init
/* 212073 0x80174C64 00000000 */ nop
/* 212074 0x80174C68 3C08801F */ lui	$t0, %hi(gStaticContext)
/* 212075 0x80174C6C 8D083F60 */ lw	$t0, %lo(gStaticContext)($t0)
/* 212076 0x80174C70 3C108020 */ lui	$s0, %hi(siEventCallbackQueue)
/* 212077 0x80174C74 26108160 */ addiu	$s0, $s0, %lo(siEventCallbackQueue)
/* 212078 0x80174C78 3C058020 */ lui	$a1, %hi(siEventCallbackBuffer)
/* 212079 0x80174C7C 24A58178 */ addiu	$a1, $a1, %lo(siEventCallbackBuffer)
/* 212080 0x80174C80 02002025 */ move	$a0, $s0
/* 212081 0x80174C84 24060001 */ li	$a2, 0X1
/* 212082 0x80174C88 0C023C90 */ jal	osCreateMesgQueue
/* 212083 0x80174C8C A50000D4 */ sh	$zero, 0XD4($t0)
/* 212084 0x80174C90 24040005 */ li	$a0, 0X5
/* 212085 0x80174C94 02002825 */ move	$a1, $s0
/* 212086 0x80174C98 0C023590 */ jal	osSetEventMesg
/* 212087 0x80174C9C 00003025 */ move	$a2, $zero
/* 212088 0x80174CA0 3C138020 */ lui	$s3, %hi(mainIrqmgrCallbackQueue)
/* 212089 0x80174CA4 26738500 */ addiu	$s3, $s3, %lo(mainIrqmgrCallbackQueue)
/* 212090 0x80174CA8 3C058020 */ lui	$a1, %hi(mainIrqCallbackBuffer)
/* 212091 0x80174CAC 24A58518 */ addiu	$a1, $a1, %lo(mainIrqCallbackBuffer)
/* 212092 0x80174CB0 02602025 */ move	$a0, $s3
/* 212093 0x80174CB4 0C023C90 */ jal	osCreateMesgQueue
/* 212094 0x80174CB8 2406003C */ li	$a2, 0X3C
/* 212095 0x80174CBC 3C118020 */ lui	$s1, %hi(audioStack)
/* 212096 0x80174CC0 3C0A801E */ lui	$t2, %hi(schedThreadName)
/* 212097 0x80174CC4 2631A5B8 */ addiu	$s1, $s1, %lo(audioStack)
/* 212098 0x80174CC8 254AFD70 */ addiu	$t2, $t2, %lo(schedThreadName)
/* 212099 0x80174CCC 3C048020 */ lui	$a0, %hi(schedStackEntry)
/* 212100 0x80174CD0 3C058020 */ lui	$a1, %hi(schedStack)
/* 212101 0x80174CD4 24090100 */ li	$t1, 0X100
/* 212102 0x80174CD8 AFA90010 */ sw	$t1, 0X10($sp)
/* 212103 0x80174CDC 24A59FB8 */ addiu	$a1, $a1, %lo(schedStack)
/* 212104 0x80174CE0 2484B2D8 */ addiu	$a0, $a0, %lo(schedStackEntry)
/* 212105 0x80174CE4 AFAA0014 */ sw	$t2, 0X14($sp)
/* 212106 0x80174CE8 02203025 */ move	$a2, $s1
/* 212107 0x80174CEC 0C0214C8 */ jal	StackCheck_Init
/* 212108 0x80174CF0 00003825 */ move	$a3, $zero
/* 212109 0x80174CF4 3C128020 */ lui	$s2, %hi(schedContext)
/* 212110 0x80174CF8 3C0C800A */ lui	$t4, %hi(irqmgrContext)
/* 212111 0x80174CFC 265281C0 */ addiu	$s2, $s2, %lo(schedContext)
/* 212112 0x80174D00 258C9EF0 */ addiu	$t4, $t4, %lo(irqmgrContext)
/* 212113 0x80174D04 3C07800A */ lui	$a3, %hi(D_8009B290)
/* 212114 0x80174D08 240B0001 */ li	$t3, 0X1
/* 212115 0x80174D0C AFAB0010 */ sw	$t3, 0X10($sp)
/* 212116 0x80174D10 90E7B290 */ lbu	$a3, %lo(D_8009B290)($a3)
/* 212117 0x80174D14 AFAC0014 */ sw	$t4, 0X14($sp)
/* 212118 0x80174D18 02402025 */ move	$a0, $s2
/* 212119 0x80174D1C 02202825 */ move	$a1, $s1
/* 212120 0x80174D20 0C05DCA8 */ jal	Sched_Start
/* 212121 0x80174D24 24060010 */ li	$a2, 0X10
/* 212122 0x80174D28 0C020627 */ jal	CIC6105_AddRomInfoFaultPage
/* 212123 0x80174D2C 00000000 */ nop
/* 212124 0x80174D30 3C04800A */ lui	$a0, %hi(irqmgrContext)
/* 212125 0x80174D34 3C058020 */ lui	$a1, %hi(mainIrqmgrCallbackNode)
/* 212126 0x80174D38 24A584F8 */ addiu	$a1, $a1, %lo(mainIrqmgrCallbackNode)
/* 212127 0x80174D3C 24849EF0 */ addiu	$a0, $a0, %lo(irqmgrContext)
/* 212128 0x80174D40 0C020494 */ jal	IrqMgr_AddClient
/* 212129 0x80174D44 02603025 */ move	$a2, $s3
/* 212130 0x80174D48 3C118020 */ lui	$s1, %hi(padmgrStack)
/* 212131 0x80174D4C 3C0E801E */ lui	$t6, %hi(audioThreadName)
/* 212132 0x80174D50 2631ADB8 */ addiu	$s1, $s1, %lo(padmgrStack)
/* 212133 0x80174D54 25CEFD78 */ addiu	$t6, $t6, %lo(audioThreadName)
/* 212134 0x80174D58 3C048020 */ lui	$a0, %hi(audioStackEntry)
/* 212135 0x80174D5C 3C058020 */ lui	$a1, %hi(audioStack)
/* 212136 0x80174D60 240D0100 */ li	$t5, 0X100
/* 212137 0x80174D64 AFAD0010 */ sw	$t5, 0X10($sp)
/* 212138 0x80174D68 24A5A5B8 */ addiu	$a1, $a1, %lo(audioStack)
/* 212139 0x80174D6C 2484B2F8 */ addiu	$a0, $a0, %lo(audioStackEntry)
/* 212140 0x80174D70 AFAE0014 */ sw	$t6, 0X14($sp)
/* 212141 0x80174D74 02203025 */ move	$a2, $s1
/* 212142 0x80174D78 0C0214C8 */ jal	StackCheck_Init
/* 212143 0x80174D7C 00003825 */ move	$a3, $zero
/* 212144 0x80174D80 3C0F800A */ lui	$t7, %hi(irqmgrContext)
/* 212145 0x80174D84 25EF9EF0 */ addiu	$t7, $t7, %lo(irqmgrContext)
/* 212146 0x80174D88 3C048020 */ lui	$a0, %hi(audioContext)
/* 212147 0x80174D8C 2484B338 */ addiu	$a0, $a0, %lo(audioContext)
/* 212148 0x80174D90 AFAF0014 */ sw	$t7, 0X14($sp)
/* 212149 0x80174D94 02202825 */ move	$a1, $s1
/* 212150 0x80174D98 2406000B */ li	$a2, 0XB
/* 212151 0x80174D9C 2407000A */ li	$a3, 0XA
/* 212152 0x80174DA0 0C05CC1D */ jal	Audio_Start
/* 212153 0x80174DA4 AFB20010 */ sw	$s2, 0X10($sp)
/* 212154 0x80174DA8 3C118020 */ lui	$s1, %hi(graphStackEntry)
/* 212155 0x80174DAC 3C19801E */ lui	$t9, %hi(padmgrThreadName)
/* 212156 0x80174DB0 2631B2B8 */ addiu	$s1, $s1, %lo(graphStackEntry)
/* 212157 0x80174DB4 2739FD80 */ addiu	$t9, $t9, %lo(padmgrThreadName)
/* 212158 0x80174DB8 3C048020 */ lui	$a0, %hi(padmgrStackEntry)
/* 212159 0x80174DBC 3C058020 */ lui	$a1, %hi(padmgrStack)
/* 212160 0x80174DC0 24180100 */ li	$t8, 0X100
/* 212161 0x80174DC4 AFB80010 */ sw	$t8, 0X10($sp)
/* 212162 0x80174DC8 24A5ADB8 */ addiu	$a1, $a1, %lo(padmgrStack)
/* 212163 0x80174DCC 2484B318 */ addiu	$a0, $a0, %lo(padmgrStackEntry)
/* 212164 0x80174DD0 AFB90014 */ sw	$t9, 0X14($sp)
/* 212165 0x80174DD4 02203025 */ move	$a2, $s1
/* 212166 0x80174DD8 0C0214C8 */ jal	StackCheck_Init
/* 212167 0x80174DDC 00003825 */ move	$a3, $zero
/* 212168 0x80174DE0 3C05800A */ lui	$a1, %hi(irqmgrContext)
/* 212169 0x80174DE4 24A59EF0 */ addiu	$a1, $a1, %lo(irqmgrContext)
/* 212170 0x80174DE8 02002025 */ move	$a0, $s0
/* 212171 0x80174DEC 24060007 */ li	$a2, 0X7
/* 212172 0x80174DF0 2407000F */ li	$a3, 0XF
/* 212173 0x80174DF4 0C05D865 */ jal	Padmgr_Start
/* 212174 0x80174DF8 AFB10010 */ sw	$s1, 0X10($sp)
/* 212175 0x80174DFC 3C048020 */ lui	$a0, %hi(audioContext)
/* 212176 0x80174E00 0C05CC12 */ jal	Audio_WaitForInit
/* 212177 0x80174E04 2484B338 */ addiu	$a0, $a0, %lo(audioContext)
/* 212178 0x80174E08 3C108020 */ lui	$s0, %hi(schedStack)
/* 212179 0x80174E0C 3C09801E */ lui	$t1, %hi(graphThreadName)
/* 212180 0x80174E10 26109FB8 */ addiu	$s0, $s0, %lo(schedStack)
/* 212181 0x80174E14 2529FD88 */ addiu	$t1, $t1, %lo(graphThreadName)
/* 212182 0x80174E18 3C048020 */ lui	$a0, %hi(graphStackEntry)
/* 212183 0x80174E1C 3C058020 */ lui	$a1, %hi(graphStack)
/* 212184 0x80174E20 24080100 */ li	$t0, 0X100
/* 212185 0x80174E24 AFA80010 */ sw	$t0, 0X10($sp)
/* 212186 0x80174E28 24A587B8 */ addiu	$a1, $a1, %lo(graphStack)
/* 212187 0x80174E2C 2484B2B8 */ addiu	$a0, $a0, %lo(graphStackEntry)
/* 212188 0x80174E30 AFA90014 */ sw	$t1, 0X14($sp)
/* 212189 0x80174E34 02003025 */ move	$a2, $s0
/* 212190 0x80174E38 0C0214C8 */ jal	StackCheck_Init
/* 212191 0x80174E3C 00003825 */ move	$a3, $zero
/* 212192 0x80174E40 3C048020 */ lui	$a0, %hi(graphOSThread)
/* 212193 0x80174E44 3C068017 */ lui	$a2, %hi(Graph_ThreadEntry)
/* 212194 0x80174E48 240A0009 */ li	$t2, 0X9
/* 212195 0x80174E4C AFAA0014 */ sw	$t2, 0X14($sp)
/* 212196 0x80174E50 24C648A0 */ addiu	$a2, $a2, %lo(Graph_ThreadEntry)
/* 212197 0x80174E54 24848608 */ addiu	$a0, $a0, %lo(graphOSThread)
/* 212198 0x80174E58 24050004 */ li	$a1, 0X4
/* 212199 0x80174E5C 8FA70048 */ lw	$a3, 0X48($sp)
/* 212200 0x80174E60 0C022790 */ jal	osCreateThread
/* 212201 0x80174E64 AFB00010 */ sw	$s0, 0X10($sp)
/* 212202 0x80174E68 3C048020 */ lui	$a0, %hi(graphOSThread)
/* 212203 0x80174E6C 0C0255EC */ jal	osStartThread
/* 212204 0x80174E70 24848608 */ addiu	$a0, $a0, %lo(graphOSThread)
/* 212205 0x80174E74 00008025 */ move	$s0, $zero
/* 212206 0x80174E78 24120004 */ li	$s2, 0X4
/* 212207 0x80174E7C 24110003 */ li	$s1, 0X3
/* 212208 0x80174E80 AFA00038 */ sw	$zero, 0X38($sp)
.L80174E84:
/* 212209 0x80174E84 02602025 */ move	$a0, $s3
/* 212210 0x80174E88 27A50038 */ addiu	$a1, $sp, 0X38
/* 212211 0x80174E8C 0C021FB4 */ jal	osRecvMesg
/* 212212 0x80174E90 24060001 */ li	$a2, 0X1
/* 212213 0x80174E94 8FAB0038 */ lw	$t3, 0X38($sp)
/* 212214 0x80174E98 1160000D */ beqz	$t3, .L80174ED0
/* 212215 0x80174E9C 00000000 */ nop
/* 212216 0x80174EA0 85620000 */ lh	$v0, 0X0($t3)
/* 212217 0x80174EA4 50510008 */ beql	$v0, $s1, .L80174EC8
/* 212218 0x80174EA8 24100001 */ li	$s0, 0X1
/* 212219 0x80174EAC 14520006 */ bne	$v0, $s2, .L80174EC8
/* 212220 0x80174EB0 00000000 */ nop
/* 212221 0x80174EB4 0C043059 */ jal	Nmi_SetPrenmiStart
/* 212222 0x80174EB8 00000000 */ nop
/* 212223 0x80174EBC 10000002 */ b	.L80174EC8
/* 212224 0x80174EC0 00000000 */ nop
/* 212225 0x80174EC4 24100001 */ li	$s0, 0X1
.L80174EC8:
/* 212226 0x80174EC8 5200FFEE */ beqzl	$s0, .L80174E84
/* 212227 0x80174ECC AFA00038 */ sw	$zero, 0X38($sp)
.L80174ED0:
/* 212228 0x80174ED0 3C04800A */ lui	$a0, %hi(irqmgrContext)
/* 212229 0x80174ED4 3C058020 */ lui	$a1, %hi(mainIrqmgrCallbackNode)
/* 212230 0x80174ED8 24A584F8 */ addiu	$a1, $a1, %lo(mainIrqmgrCallbackNode)
/* 212231 0x80174EDC 0C0204B7 */ jal	IrqMgr_RemoveClient
/* 212232 0x80174EE0 24849EF0 */ addiu	$a0, $a0, %lo(irqmgrContext)
/* 212233 0x80174EE4 3C048020 */ lui	$a0, %hi(graphOSThread)
/* 212234 0x80174EE8 0C02251C */ jal	osDestroyThread
/* 212235 0x80174EEC 24848608 */ addiu	$a0, $a0, %lo(graphOSThread)
/* 212236 0x80174EF0 8FBF002C */ lw	$ra, 0X2C($sp)
/* 212237 0x80174EF4 8FB0001C */ lw	$s0, 0X1C($sp)
/* 212238 0x80174EF8 8FB10020 */ lw	$s1, 0X20($sp)
/* 212239 0x80174EFC 8FB20024 */ lw	$s2, 0X24($sp)
/* 212240 0x80174F00 8FB30028 */ lw	$s3, 0X28($sp)
/* 212241 0x80174F04 03E00008 */ jr	$ra
/* 212242 0x80174F08 27BD0048 */ addiu	$sp, $sp, 0X48
/* 212243 0x80174F0C 00000000 */ nop
