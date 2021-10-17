.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osPfsSelectBank
/* 019176 0x80092C00 27BDFFA8 */ addiu	$sp, $sp, -0X58
/* 019177 0x80092C04 AFB00020 */ sw	$s0, 0X20($sp)
/* 019178 0x80092C08 30B000FF */ andi	$s0, $a1, 0XFF
/* 019179 0x80092C0C AFBF0024 */ sw	$ra, 0X24($sp)
/* 019180 0x80092C10 AFA40058 */ sw	$a0, 0X58($sp)
/* 019181 0x80092C14 AFA5005C */ sw	$a1, 0X5C($sp)
/* 019182 0x80092C18 27A20038 */ addiu	$v0, $sp, 0X38
/* 019183 0x80092C1C 27A30058 */ addiu	$v1, $sp, 0X58
.L80092C20:
/* 019184 0x80092C20 24420004 */ addiu	$v0, $v0, 0X4
/* 019185 0x80092C24 A050FFFD */ sb	$s0, -0X3($v0)
/* 019186 0x80092C28 A050FFFE */ sb	$s0, -0X2($v0)
/* 019187 0x80092C2C A050FFFF */ sb	$s0, -0X1($v0)
/* 019188 0x80092C30 1443FFFB */ bne	$v0, $v1, .L80092C20
/* 019189 0x80092C34 A050FFFC */ sb	$s0, -0X4($v0)
/* 019190 0x80092C38 8FAE0058 */ lw	$t6, 0X58($sp)
/* 019191 0x80092C3C 24060400 */ li	$a2, 0X400
/* 019192 0x80092C40 27A70038 */ addiu	$a3, $sp, 0X38
/* 019193 0x80092C44 8DC40004 */ lw	$a0, 0X4($t6)
/* 019194 0x80092C48 8DC50008 */ lw	$a1, 0X8($t6)
/* 019195 0x80092C4C 0C024F68 */ jal	__osContRamWrite
/* 019196 0x80092C50 AFA00010 */ sw	$zero, 0X10($sp)
/* 019197 0x80092C54 14400003 */ bnez	$v0, .L80092C64
/* 019198 0x80092C58 00401825 */ move	$v1, $v0
/* 019199 0x80092C5C 8FAF0058 */ lw	$t7, 0X58($sp)
/* 019200 0x80092C60 A1F00065 */ sb	$s0, 0X65($t7)
.L80092C64:
/* 019201 0x80092C64 8FBF0024 */ lw	$ra, 0X24($sp)
/* 019202 0x80092C68 8FB00020 */ lw	$s0, 0X20($sp)
/* 019203 0x80092C6C 27BD0058 */ addiu	$sp, $sp, 0X58
/* 019204 0x80092C70 03E00008 */ jr	$ra
/* 019205 0x80092C74 00601025 */ move	$v0, $v1
/* 019206 0x80092C78 00000000 */ nop
/* 019207 0x80092C7C 00000000 */ nop
