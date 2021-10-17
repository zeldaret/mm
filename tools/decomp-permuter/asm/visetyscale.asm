.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osViSetYScale
/* 022056 0x80095900 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 022057 0x80095904 AFBF0014 */ sw	$ra, 0X14($sp)
/* 022058 0x80095908 0C024698 */ jal	__osDisableInt
/* 022059 0x8009590C E7AC0018 */ swc1	$f12, 0X18($sp)
/* 022060 0x80095910 3C05800A */ lui	$a1, %hi(__osViNext)
/* 022061 0x80095914 24A580C4 */ addiu	$a1, $a1, %lo(__osViNext)
/* 022062 0x80095918 8CAE0000 */ lw	$t6, 0X0($a1)
/* 022063 0x8009591C C7A40018 */ lwc1	$f4, 0X18($sp)
/* 022064 0x80095920 00402025 */ move	$a0, $v0
/* 022065 0x80095924 E5C40024 */ swc1	$f4, 0X24($t6)
/* 022066 0x80095928 8CA30000 */ lw	$v1, 0X0($a1)
/* 022067 0x8009592C 946F0000 */ lhu	$t7, 0X0($v1)
/* 022068 0x80095930 35F80004 */ ori	$t8, $t7, 0X4
/* 022069 0x80095934 0C0246B4 */ jal	__osRestoreInt
/* 022070 0x80095938 A4780000 */ sh	$t8, 0X0($v1)
/* 022071 0x8009593C 8FBF0014 */ lw	$ra, 0X14($sp)
/* 022072 0x80095940 27BD0018 */ addiu	$sp, $sp, 0X18
/* 022073 0x80095944 03E00008 */ jr	$ra
/* 022074 0x80095948 00000000 */ nop
/* 022075 0x8009594C 00000000 */ nop
