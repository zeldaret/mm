.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osCreateMesgQueue
/* 015480 0x8008F240 3C0E8009 */ lui	$t6, %hi(__osThreadTail)
/* 015481 0x8008F244 3C0F8009 */ lui	$t7, %hi(__osThreadTail)
/* 015482 0x8008F248 25CE7E10 */ addiu	$t6, $t6, %lo(__osThreadTail)
/* 015483 0x8008F24C 25EF7E10 */ addiu	$t7, $t7, %lo(__osThreadTail)
/* 015484 0x8008F250 AC8E0000 */ sw	$t6, 0X0($a0)
/* 015485 0x8008F254 AC8F0004 */ sw	$t7, 0X4($a0)
/* 015486 0x8008F258 AC800008 */ sw	$zero, 0X8($a0)
/* 015487 0x8008F25C AC80000C */ sw	$zero, 0XC($a0)
/* 015488 0x8008F260 AC860010 */ sw	$a2, 0X10($a0)
/* 015489 0x8008F264 03E00008 */ jr	$ra
/* 015490 0x8008F268 AC850014 */ sw	$a1, 0X14($a0)
/* 015491 0x8008F26C 00000000 */ nop
