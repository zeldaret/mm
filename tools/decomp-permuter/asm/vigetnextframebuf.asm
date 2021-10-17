.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osViGetNextFramebuffer
/* 010860 0x8008AA10 27BDFFE0 */ addiu	$sp, $sp, -0X20
/* 010861 0x8008AA14 AFBF0014 */ sw	$ra, 0X14($sp)
/* 010862 0x8008AA18 0C024698 */ jal	__osDisableInt
/* 010863 0x8008AA1C 00000000 */ nop
/* 010864 0x8008AA20 3C0E800A */ lui	$t6, %hi(__osViNext)
/* 010865 0x8008AA24 8DCE80C4 */ lw	$t6, %lo(__osViNext)($t6)
/* 010866 0x8008AA28 00402025 */ move	$a0, $v0
/* 010867 0x8008AA2C 8DCF0004 */ lw	$t7, 0X4($t6)
/* 010868 0x8008AA30 0C0246B4 */ jal	__osRestoreInt
/* 010869 0x8008AA34 AFAF0018 */ sw	$t7, 0X18($sp)
/* 010870 0x8008AA38 8FBF0014 */ lw	$ra, 0X14($sp)
/* 010871 0x8008AA3C 8FA20018 */ lw	$v0, 0X18($sp)
/* 010872 0x8008AA40 27BD0020 */ addiu	$sp, $sp, 0X20
/* 010873 0x8008AA44 03E00008 */ jr	$ra
/* 010874 0x8008AA48 00000000 */ nop
/* 010875 0x8008AA4C 00000000 */ nop
