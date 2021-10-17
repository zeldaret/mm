.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel osContSetCh
/* 019208 0x80092C80 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 019209 0x80092C84 AFBF0014 */ sw	$ra, 0X14($sp)
/* 019210 0x80092C88 0C0226BC */ jal	__osSiGetAccess
/* 019211 0x80092C8C AFA40018 */ sw	$a0, 0X18($sp)
/* 019212 0x80092C90 93A2001B */ lbu	$v0, 0X1B($sp)
/* 019213 0x80092C94 240E0004 */ li	$t6, 0X4
/* 019214 0x80092C98 240F00FE */ li	$t7, 0XFE
/* 019215 0x80092C9C 28410005 */ slti	$at, $v0, 0X5
/* 019216 0x80092CA0 14200003 */ bnez	$at, .L80092CB0
/* 019217 0x80092CA4 3C01800A */ lui	$at, %hi(__osMaxControllers)
/* 019218 0x80092CA8 10000003 */ b	.L80092CB8
/* 019219 0x80092CAC A02ECF11 */ sb	$t6, %lo(__osMaxControllers)($at)
.L80092CB0:
/* 019220 0x80092CB0 3C01800A */ lui	$at, %hi(__osMaxControllers)
/* 019221 0x80092CB4 A022CF11 */ sb	$v0, %lo(__osMaxControllers)($at)
.L80092CB8:
/* 019222 0x80092CB8 3C01800A */ lui	$at, %hi(__osContLastCmd)
/* 019223 0x80092CBC 0C0226CD */ jal	__osSiRelAccess
/* 019224 0x80092CC0 A02FCF10 */ sb	$t7, %lo(__osContLastCmd)($at)
/* 019225 0x80092CC4 8FBF0014 */ lw	$ra, 0X14($sp)
/* 019226 0x80092CC8 27BD0018 */ addiu	$sp, $sp, 0X18
/* 019227 0x80092CCC 00001025 */ move	$v0, $zero
/* 019228 0x80092CD0 03E00008 */ jr	$ra
/* 019229 0x80092CD4 00000000 */ nop
/* 019230 0x80092CD8 00000000 */ nop
/* 019231 0x80092CDC 00000000 */ nop
