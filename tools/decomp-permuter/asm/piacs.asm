.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osPiCreateAccessQueue
/* 012364 0x8008C190 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 012365 0x8008C194 AFBF0014 */ sw	$ra, 0X14($sp)
/* 012366 0x8008C198 240E0001 */ li	$t6, 0X1
/* 012367 0x8008C19C 3C018009 */ lui	$at, %hi(__osPiAccessQueueEnabled)
/* 012368 0x8008C1A0 3C04800A */ lui	$a0, %hi(__osPiAccessQueue)
/* 012369 0x8008C1A4 3C05800A */ lui	$a1, %hi(D_8009E3F0)
/* 012370 0x8008C1A8 AC2E7EA0 */ sw	$t6, %lo(__osPiAccessQueueEnabled)($at)
/* 012371 0x8008C1AC 24A5E3F0 */ addiu	$a1, $a1, %lo(D_8009E3F0)
/* 012372 0x8008C1B0 2484E3F8 */ addiu	$a0, $a0, %lo(__osPiAccessQueue)
/* 012373 0x8008C1B4 0C023C90 */ jal	osCreateMesgQueue
/* 012374 0x8008C1B8 24060001 */ li	$a2, 0X1
/* 012375 0x8008C1BC 3C04800A */ lui	$a0, %hi(__osPiAccessQueue)
/* 012376 0x8008C1C0 2484E3F8 */ addiu	$a0, $a0, %lo(__osPiAccessQueue)
/* 012377 0x8008C1C4 00002825 */ move	$a1, $zero
/* 012378 0x8008C1C8 0C021EC4 */ jal	osSendMesg
/* 012379 0x8008C1CC 00003025 */ move	$a2, $zero
/* 012380 0x8008C1D0 8FBF0014 */ lw	$ra, 0X14($sp)
/* 012381 0x8008C1D4 27BD0018 */ addiu	$sp, $sp, 0X18
/* 012382 0x8008C1D8 03E00008 */ jr	$ra
/* 012383 0x8008C1DC 00000000 */ nop

glabel __osPiGetAccess
/* 012384 0x8008C1E0 3C0E8009 */ lui	$t6, %hi(__osPiAccessQueueEnabled)
/* 012385 0x8008C1E4 8DCE7EA0 */ lw	$t6, %lo(__osPiAccessQueueEnabled)($t6)
/* 012386 0x8008C1E8 27BDFFE0 */ addiu	$sp, $sp, -0X20
/* 012387 0x8008C1EC AFBF0014 */ sw	$ra, 0X14($sp)
/* 012388 0x8008C1F0 15C00003 */ bnez	$t6, .L8008C200
/* 012389 0x8008C1F4 00000000 */ nop
/* 012390 0x8008C1F8 0C023064 */ jal	__osPiCreateAccessQueue
/* 012391 0x8008C1FC 00000000 */ nop
.L8008C200:
/* 012392 0x8008C200 3C04800A */ lui	$a0, %hi(__osPiAccessQueue)
/* 012393 0x8008C204 2484E3F8 */ addiu	$a0, $a0, %lo(__osPiAccessQueue)
/* 012394 0x8008C208 27A5001C */ addiu	$a1, $sp, 0X1C
/* 012395 0x8008C20C 0C021FB4 */ jal	osRecvMesg
/* 012396 0x8008C210 24060001 */ li	$a2, 0X1
/* 012397 0x8008C214 8FBF0014 */ lw	$ra, 0X14($sp)
/* 012398 0x8008C218 27BD0020 */ addiu	$sp, $sp, 0X20
/* 012399 0x8008C21C 03E00008 */ jr	$ra
/* 012400 0x8008C220 00000000 */ nop

glabel __osPiRelAccess
/* 012401 0x8008C224 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 012402 0x8008C228 AFBF0014 */ sw	$ra, 0X14($sp)
/* 012403 0x8008C22C 3C04800A */ lui	$a0, %hi(__osPiAccessQueue)
/* 012404 0x8008C230 2484E3F8 */ addiu	$a0, $a0, %lo(__osPiAccessQueue)
/* 012405 0x8008C234 00002825 */ move	$a1, $zero
/* 012406 0x8008C238 0C021EC4 */ jal	osSendMesg
/* 012407 0x8008C23C 00003025 */ move	$a2, $zero
/* 012408 0x8008C240 8FBF0014 */ lw	$ra, 0X14($sp)
/* 012409 0x8008C244 27BD0018 */ addiu	$sp, $sp, 0X18
/* 012410 0x8008C248 03E00008 */ jr	$ra
/* 012411 0x8008C24C 00000000 */ nop
/* 012412 0x8008C250 00000000 */ nop
/* 012413 0x8008C254 00000000 */ nop
/* 012414 0x8008C258 00000000 */ nop
/* 012415 0x8008C25C 00000000 */ nop
