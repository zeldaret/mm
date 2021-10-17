.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel zelda_malloc
/* 095336 0x80102C60 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 095337 0x80102C64 AFBF0014 */ sw	$ra, 0X14($sp)
/* 095338 0x80102C68 00802825 */ move	$a1, $a0
/* 095339 0x80102C6C 3C04801F */ lui	$a0, %hi(mainHeap)
/* 095340 0x80102C70 0C021CC9 */ jal	__osMalloc
/* 095341 0x80102C74 24845100 */ addiu	$a0, $a0, %lo(mainHeap)
/* 095342 0x80102C78 8FBF0014 */ lw	$ra, 0X14($sp)
/* 095343 0x80102C7C 27BD0018 */ addiu	$sp, $sp, 0X18
/* 095344 0x80102C80 03E00008 */ jr	$ra
/* 095345 0x80102C84 00000000 */ nop

glabel zelda_mallocR
/* 095346 0x80102C88 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 095347 0x80102C8C AFBF0014 */ sw	$ra, 0X14($sp)
/* 095348 0x80102C90 00802825 */ move	$a1, $a0
/* 095349 0x80102C94 3C04801F */ lui	$a0, %hi(mainHeap)
/* 095350 0x80102C98 0C021D02 */ jal	__osMallocR
/* 095351 0x80102C9C 24845100 */ addiu	$a0, $a0, %lo(mainHeap)
/* 095352 0x80102CA0 8FBF0014 */ lw	$ra, 0X14($sp)
/* 095353 0x80102CA4 27BD0018 */ addiu	$sp, $sp, 0X18
/* 095354 0x80102CA8 03E00008 */ jr	$ra
/* 095355 0x80102CAC 00000000 */ nop

glabel zelda_realloc
/* 095356 0x80102CB0 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 095357 0x80102CB4 00A03025 */ move	$a2, $a1
/* 095358 0x80102CB8 00802825 */ move	$a1, $a0
/* 095359 0x80102CBC AFBF0014 */ sw	$ra, 0X14($sp)
/* 095360 0x80102CC0 AFA40018 */ sw	$a0, 0X18($sp)
/* 095361 0x80102CC4 3C04801F */ lui	$a0, %hi(mainHeap)
/* 095362 0x80102CC8 0C021D79 */ jal	__osRealloc
/* 095363 0x80102CCC 24845100 */ addiu	$a0, $a0, %lo(mainHeap)
/* 095364 0x80102CD0 8FBF0014 */ lw	$ra, 0X14($sp)
/* 095365 0x80102CD4 27BD0018 */ addiu	$sp, $sp, 0X18
/* 095366 0x80102CD8 03E00008 */ jr	$ra
/* 095367 0x80102CDC 00000000 */ nop

glabel zelda_free
/* 095368 0x80102CE0 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 095369 0x80102CE4 AFBF0014 */ sw	$ra, 0X14($sp)
/* 095370 0x80102CE8 00802825 */ move	$a1, $a0
/* 095371 0x80102CEC 3C04801F */ lui	$a0, %hi(mainHeap)
/* 095372 0x80102CF0 0C021D3B */ jal	__osFree
/* 095373 0x80102CF4 24845100 */ addiu	$a0, $a0, %lo(mainHeap)
/* 095374 0x80102CF8 8FBF0014 */ lw	$ra, 0X14($sp)
/* 095375 0x80102CFC 27BD0018 */ addiu	$sp, $sp, 0X18
/* 095376 0x80102D00 03E00008 */ jr	$ra
/* 095377 0x80102D04 00000000 */ nop

glabel zelda_calloc
/* 095378 0x80102D08 27BDFFD8 */ addiu	$sp, $sp, -0X28
/* 095379 0x80102D0C AFBF0014 */ sw	$ra, 0X14($sp)
/* 095380 0x80102D10 00803025 */ move	$a2, $a0
/* 095381 0x80102D14 00A03825 */ move	$a3, $a1
/* 095382 0x80102D18 00C70019 */ multu	$a2, $a3
/* 095383 0x80102D1C 3C04801F */ lui	$a0, %hi(mainHeap)
/* 095384 0x80102D20 24845100 */ addiu	$a0, $a0, %lo(mainHeap)
/* 095385 0x80102D24 00002812 */ mflo	$a1
/* 095386 0x80102D28 AFA5001C */ sw	$a1, 0X1C($sp)
/* 095387 0x80102D2C 0C021CC9 */ jal	__osMalloc
/* 095388 0x80102D30 00000000 */ nop
/* 095389 0x80102D34 8FA5001C */ lw	$a1, 0X1C($sp)
/* 095390 0x80102D38 10400004 */ beqz	$v0, .L80102D4C
/* 095391 0x80102D3C 00402025 */ move	$a0, $v0
/* 095392 0x80102D40 0C02258C */ jal	bzero
/* 095393 0x80102D44 AFA20024 */ sw	$v0, 0X24($sp)
/* 095394 0x80102D48 8FA40024 */ lw	$a0, 0X24($sp)
.L80102D4C:
/* 095395 0x80102D4C 00801025 */ move	$v0, $a0
/* 095396 0x80102D50 8FBF0014 */ lw	$ra, 0X14($sp)
/* 095397 0x80102D54 27BD0028 */ addiu	$sp, $sp, 0X28
/* 095398 0x80102D58 03E00008 */ jr	$ra
/* 095399 0x80102D5C 00000000 */ nop

glabel MainHeap_AnalyzeArena
/* 095400 0x80102D60 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 095401 0x80102D64 AFA5001C */ sw	$a1, 0X1C($sp)
/* 095402 0x80102D68 00C03825 */ move	$a3, $a2
/* 095403 0x80102D6C 8FA6001C */ lw	$a2, 0X1C($sp)
/* 095404 0x80102D70 00802825 */ move	$a1, $a0
/* 095405 0x80102D74 AFBF0014 */ sw	$ra, 0X14($sp)
/* 095406 0x80102D78 AFA40018 */ sw	$a0, 0X18($sp)
/* 095407 0x80102D7C 3C04801F */ lui	$a0, %hi(mainHeap)
/* 095408 0x80102D80 0C021DC5 */ jal	__osAnalyzeArena
/* 095409 0x80102D84 24845100 */ addiu	$a0, $a0, %lo(mainHeap)
/* 095410 0x80102D88 8FBF0014 */ lw	$ra, 0X14($sp)
/* 095411 0x80102D8C 27BD0018 */ addiu	$sp, $sp, 0X18
/* 095412 0x80102D90 03E00008 */ jr	$ra
/* 095413 0x80102D94 00000000 */ nop

glabel MainHeap_Check
/* 095414 0x80102D98 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 095415 0x80102D9C AFBF0014 */ sw	$ra, 0X14($sp)
/* 095416 0x80102DA0 3C04801F */ lui	$a0, %hi(mainHeap)
/* 095417 0x80102DA4 0C021DF1 */ jal	__osCheckArena
/* 095418 0x80102DA8 24845100 */ addiu	$a0, $a0, %lo(mainHeap)
/* 095419 0x80102DAC 8FBF0014 */ lw	$ra, 0X14($sp)
/* 095420 0x80102DB0 27BD0018 */ addiu	$sp, $sp, 0X18
/* 095421 0x80102DB4 03E00008 */ jr	$ra
/* 095422 0x80102DB8 00000000 */ nop

glabel MainHeap_Init
/* 095423 0x80102DBC 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 095424 0x80102DC0 00A03025 */ move	$a2, $a1
/* 095425 0x80102DC4 00802825 */ move	$a1, $a0
/* 095426 0x80102DC8 AFBF0014 */ sw	$ra, 0X14($sp)
/* 095427 0x80102DCC AFA40018 */ sw	$a0, 0X18($sp)
/* 095428 0x80102DD0 3C04801F */ lui	$a0, %hi(mainHeap)
/* 095429 0x80102DD4 0C021C83 */ jal	__osMallocInit
/* 095430 0x80102DD8 24845100 */ addiu	$a0, $a0, %lo(mainHeap)
/* 095431 0x80102DDC 8FBF0014 */ lw	$ra, 0X14($sp)
/* 095432 0x80102DE0 27BD0018 */ addiu	$sp, $sp, 0X18
/* 095433 0x80102DE4 03E00008 */ jr	$ra
/* 095434 0x80102DE8 00000000 */ nop

glabel MainHeap_Cleanup
/* 095435 0x80102DEC 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 095436 0x80102DF0 AFBF0014 */ sw	$ra, 0X14($sp)
/* 095437 0x80102DF4 3C04801F */ lui	$a0, %hi(mainHeap)
/* 095438 0x80102DF8 0C021CBF */ jal	__osMallocCleanup
/* 095439 0x80102DFC 24845100 */ addiu	$a0, $a0, %lo(mainHeap)
/* 095440 0x80102E00 8FBF0014 */ lw	$ra, 0X14($sp)
/* 095441 0x80102E04 27BD0018 */ addiu	$sp, $sp, 0X18
/* 095442 0x80102E08 03E00008 */ jr	$ra
/* 095443 0x80102E0C 00000000 */ nop

glabel MainHeap_IsInitialized
/* 095444 0x80102E10 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 095445 0x80102E14 AFBF0014 */ sw	$ra, 0X14($sp)
/* 095446 0x80102E18 3C04801F */ lui	$a0, %hi(mainHeap)
/* 095447 0x80102E1C 0C021CC7 */ jal	__osMallocIsInitalized
/* 095448 0x80102E20 24845100 */ addiu	$a0, $a0, %lo(mainHeap)
/* 095449 0x80102E24 8FBF0014 */ lw	$ra, 0X14($sp)
/* 095450 0x80102E28 27BD0018 */ addiu	$sp, $sp, 0X18
/* 095451 0x80102E2C 03E00008 */ jr	$ra
/* 095452 0x80102E30 00000000 */ nop
/* 095453 0x80102E34 00000000 */ nop
/* 095454 0x80102E38 00000000 */ nop
/* 095455 0x80102E3C 00000000 */ nop
