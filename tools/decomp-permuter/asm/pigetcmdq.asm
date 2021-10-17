.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osPiGetCmdQueue
/* 018348 0x80091F10 3C038009 */ lui	$v1, %hi(__osPiDevMgr)
/* 018349 0x80091F14 24637E70 */ addiu	$v1, $v1, %lo(__osPiDevMgr)
/* 018350 0x80091F18 8C6E0000 */ lw	$t6, 0X0($v1)
/* 018351 0x80091F1C 55C00004 */ bnezl	$t6, .L80091F30
/* 018352 0x80091F20 8C620008 */ lw	$v0, 0X8($v1)
/* 018353 0x80091F24 03E00008 */ jr	$ra
/* 018354 0x80091F28 00001025 */ move	$v0, $zero
/* 018355 0x80091F2C 8C620008 */ lw	$v0, 0X8($v1)
.L80091F30:
/* 018356 0x80091F30 03E00008 */ jr	$ra
/* 018357 0x80091F34 00000000 */ nop
/* 018358 0x80091F38 00000000 */ nop
/* 018359 0x80091F3C 00000000 */ nop
