glabel Main_ThreadEntry
/* 000168 0x80080300 27BDFFE0 */ addiu	$sp, $sp, -0X20
/* 000169 0x80080304 AFBF001C */ sw	$ra, 0X1C($sp)
/* 000170 0x80080308 AFA40020 */ sw	$a0, 0X20($sp)
/* 000171 0x8008030C 3C0F800A */ lui	$t7, %hi(irqmgrThreadName)
/* 000172 0x80080310 25EF81A0 */ addiu	$t7, $t7, %lo(irqmgrThreadName)
/* 000173 0x80080314 3C04800A */ lui	$a0, %hi(irqmgrStackEntry)
/* 000174 0x80080318 3C05800A */ lui	$a1, %hi(irqmgrStack)
/* 000175 0x8008031C 3C06800A */ lui	$a2, %hi(irqmgrStackEntry)
/* 000176 0x80080320 240E0100 */ li	$t6, 0X100
/* 000177 0x80080324 AFAE0010 */ sw	$t6, 0X10($sp)
/* 000178 0x80080328 24C6A670 */ addiu	$a2, $a2, %lo(irqmgrStackEntry)
/* 000179 0x8008032C 24A5A170 */ addiu	$a1, $a1, %lo(irqmgrStack)
/* 000180 0x80080330 2484A670 */ addiu	$a0, $a0, %lo(irqmgrStackEntry)
/* 000181 0x80080334 AFAF0014 */ sw	$t7, 0X14($sp)
/* 000182 0x80080338 0C0214C8 */ jal	StackCheck_Init
/* 000183 0x8008033C 00003825 */ move	$a3, $zero
/* 000184 0x80080340 3C04800A */ lui	$a0, %hi(irqmgrContext)
/* 000185 0x80080344 3C05800A */ lui	$a1, %hi(irqmgrStackEntry)
/* 000186 0x80080348 24A5A670 */ addiu	$a1, $a1, %lo(irqmgrStackEntry)
/* 000187 0x8008034C 24849EF0 */ addiu	$a0, $a0, %lo(irqmgrContext)
/* 000188 0x80080350 24060012 */ li	$a2, 0X12
/* 000189 0x80080354 0C0205D5 */ jal	IrqMgr_Create
/* 000190 0x80080358 24070001 */ li	$a3, 0X1
/* 000191 0x8008035C 0C020343 */ jal	Dmamgr_Start
/* 000192 0x80080360 00000000 */ nop
/* 000193 0x80080364 0C020094 */ jal	Idle_InitCodeAndMemory
/* 000194 0x80080368 00000000 */ nop
/* 000195 0x8008036C 0C05D2FC */ jal	main
/* 000196 0x80080370 8FA40020 */ lw	$a0, 0X20($sp)
/* 000197 0x80080374 0C020380 */ jal	Dmamgr_Stop
/* 000198 0x80080378 00000000 */ nop
/* 000199 0x8008037C 8FBF001C */ lw	$ra, 0X1C($sp)
/* 000200 0x80080380 27BD0020 */ addiu	$sp, $sp, 0X20
/* 000201 0x80080384 03E00008 */ jr	$ra
/* 000202 0x80080388 00000000 */ nop

