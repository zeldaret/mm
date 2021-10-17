.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osViSetEvent
/* 018656 0x800923E0 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 018657 0x800923E4 AFBF0014 */ sw	$ra, 0X14($sp)
/* 018658 0x800923E8 AFA40018 */ sw	$a0, 0X18($sp)
/* 018659 0x800923EC AFA5001C */ sw	$a1, 0X1C($sp)
/* 018660 0x800923F0 0C024698 */ jal	__osDisableInt
/* 018661 0x800923F4 AFA60020 */ sw	$a2, 0X20($sp)
/* 018662 0x800923F8 3C03800A */ lui	$v1, %hi(__osViNext)
/* 018663 0x800923FC 246380C4 */ addiu	$v1, $v1, %lo(__osViNext)
/* 018664 0x80092400 8C6F0000 */ lw	$t7, 0X0($v1)
/* 018665 0x80092404 8FAE0018 */ lw	$t6, 0X18($sp)
/* 018666 0x80092408 00402025 */ move	$a0, $v0
/* 018667 0x8009240C ADEE0010 */ sw	$t6, 0X10($t7)
/* 018668 0x80092410 8C790000 */ lw	$t9, 0X0($v1)
/* 018669 0x80092414 8FB8001C */ lw	$t8, 0X1C($sp)
/* 018670 0x80092418 AF380014 */ sw	$t8, 0X14($t9)
/* 018671 0x8009241C 8C690000 */ lw	$t1, 0X0($v1)
/* 018672 0x80092420 8FA80020 */ lw	$t0, 0X20($sp)
/* 018673 0x80092424 0C0246B4 */ jal	__osRestoreInt
/* 018674 0x80092428 A5280002 */ sh	$t0, 0X2($t1)
/* 018675 0x8009242C 8FBF0014 */ lw	$ra, 0X14($sp)
/* 018676 0x80092430 27BD0018 */ addiu	$sp, $sp, 0X18
/* 018677 0x80092434 03E00008 */ jr	$ra
/* 018678 0x80092438 00000000 */ nop
/* 018679 0x8009243C 00000000 */ nop
