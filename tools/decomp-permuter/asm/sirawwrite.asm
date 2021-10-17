.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osSiRawWriteIo
/* 021616 0x80095220 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 021617 0x80095224 AFBF0014 */ sw	$ra, 0X14($sp)
/* 021618 0x80095228 AFA40018 */ sw	$a0, 0X18($sp)
/* 021619 0x8009522C 0C023E8C */ jal	__osSiDeviceBusy
/* 021620 0x80095230 AFA5001C */ sw	$a1, 0X1C($sp)
/* 021621 0x80095234 10400003 */ beqz	$v0, .L80095244
/* 021622 0x80095238 8FAE001C */ lw	$t6, 0X1C($sp)
/* 021623 0x8009523C 10000006 */ b	.L80095258
/* 021624 0x80095240 2402FFFF */ li	$v0, -0X1
.L80095244:
/* 021625 0x80095244 8FAF0018 */ lw	$t7, 0X18($sp)
/* 021626 0x80095248 3C01A000 */ lui	$at, 0xA000
/* 021627 0x8009524C 00001025 */ move	$v0, $zero
/* 021628 0x80095250 01E1C025 */ or	$t8, $t7, $at
/* 021629 0x80095254 AF0E0000 */ sw	$t6, 0X0($t8)
.L80095258:
/* 021630 0x80095258 8FBF0014 */ lw	$ra, 0X14($sp)
/* 021631 0x8009525C 27BD0018 */ addiu	$sp, $sp, 0X18
/* 021632 0x80095260 03E00008 */ jr	$ra
/* 021633 0x80095264 00000000 */ nop
/* 021634 0x80095268 00000000 */ nop
/* 021635 0x8009526C 00000000 */ nop
