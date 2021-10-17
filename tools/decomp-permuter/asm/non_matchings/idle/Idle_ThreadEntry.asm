glabel Idle_ThreadEntry
/* 000301 0x80080514 27BDFFE0 */ addiu	$sp, $sp, -0X20
/* 000302 0x80080518 AFBF001C */ sw	$ra, 0X1C($sp)
/* 000303 0x8008051C AFA40020 */ sw	$a0, 0X20($sp)
/* 000304 0x80080520 0C0200E3 */ jal	func_8008038C
/* 000305 0x80080524 00000000 */ nop
/* 000306 0x80080528 3C05800A */ lui	$a1, %hi(D_8009B228)
/* 000307 0x8008052C 3C06800A */ lui	$a2, %hi(D_8009B160)
/* 000308 0x80080530 24C6B160 */ addiu	$a2, $a2, %lo(D_8009B160)
/* 000309 0x80080534 24A5B228 */ addiu	$a1, $a1, %lo(D_8009B228)
/* 000310 0x80080538 24040096 */ li	$a0, 0X96
/* 000311 0x8008053C 0C023008 */ jal	osCreatePiManager
/* 000312 0x80080540 24070032 */ li	$a3, 0X32
/* 000313 0x80080544 3C0F800A */ lui	$t7, %hi(mainThreadName)
/* 000314 0x80080548 25EF81A8 */ addiu	$t7, $t7, %lo(mainThreadName)
/* 000315 0x8008054C 3C04800A */ lui	$a0, %hi(mainStackEntry)
/* 000316 0x80080550 3C05800A */ lui	$a1, %hi(mainStack)
/* 000317 0x80080554 3C06800A */ lui	$a2, %hi(mainStackEntry)
/* 000318 0x80080558 240E0400 */ li	$t6, 0X400
/* 000319 0x8008055C AFAE0010 */ sw	$t6, 0X10($sp)
/* 000320 0x80080560 24C6B140 */ addiu	$a2, $a2, %lo(mainStackEntry)
/* 000321 0x80080564 24A5A840 */ addiu	$a1, $a1, %lo(mainStack)
/* 000322 0x80080568 2484B140 */ addiu	$a0, $a0, %lo(mainStackEntry)
/* 000323 0x8008056C AFAF0014 */ sw	$t7, 0X14($sp)
/* 000324 0x80080570 0C0214C8 */ jal	StackCheck_Init
/* 000325 0x80080574 00003825 */ move	$a3, $zero
/* 000326 0x80080578 3C18800A */ lui	$t8, %hi(mainStackEntry)
/* 000327 0x8008057C 2718B140 */ addiu	$t8, $t8, %lo(mainStackEntry)
/* 000328 0x80080580 3C04800A */ lui	$a0, %hi(mainOSThread)
/* 000329 0x80080584 3C068008 */ lui	$a2, %hi(Main_ThreadEntry)
/* 000330 0x80080588 2419000C */ li	$t9, 0XC
/* 000331 0x8008058C AFB90014 */ sw	$t9, 0X14($sp)
/* 000332 0x80080590 24C60300 */ addiu	$a2, $a2, %lo(Main_ThreadEntry)
/* 000333 0x80080594 2484A690 */ addiu	$a0, $a0, %lo(mainOSThread)
/* 000334 0x80080598 AFB80010 */ sw	$t8, 0X10($sp)
/* 000335 0x8008059C 24050003 */ li	$a1, 0X3
/* 000336 0x800805A0 0C022790 */ jal	osCreateThread
/* 000337 0x800805A4 8FA70020 */ lw	$a3, 0X20($sp)
/* 000338 0x800805A8 3C04800A */ lui	$a0, %hi(mainOSThread)
/* 000339 0x800805AC 0C0255EC */ jal	osStartThread
/* 000340 0x800805B0 2484A690 */ addiu	$a0, $a0, %lo(mainOSThread)
/* 000341 0x800805B4 00002025 */ move	$a0, $zero
/* 000342 0x800805B8 0C023F00 */ jal	osSetThreadPri
/* 000343 0x800805BC 00002825 */ move	$a1, $zero
.L800805C0:
/* 000344 0x800805C0 1000FFFF */ b	.L800805C0
/* 000345 0x800805C4 00000000 */ nop
/* 000346 0x800805C8 8FBF001C */ lw	$ra, 0X1C($sp)
/* 000347 0x800805CC 27BD0020 */ addiu	$sp, $sp, 0X20
/* 000348 0x800805D0 03E00008 */ jr	$ra
/* 000349 0x800805D4 00000000 */ nop
/* 000350 0x800805D8 00000000 */ nop
/* 000351 0x800805DC 00000000 */ nop
