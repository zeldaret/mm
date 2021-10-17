.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel func_8008C640
/* 012664 0x8008C640 8FBF0044 */ lw	$ra, 0X44($sp)
/* 012665 0x8008C644 8FB00020 */ lw	$s0, 0X20($sp)
/* 012666 0x8008C648 8FB10024 */ lw	$s1, 0X24($sp)
/* 012667 0x8008C64C 8FB20028 */ lw	$s2, 0X28($sp)
/* 012668 0x8008C650 8FB3002C */ lw	$s3, 0X2C($sp)
/* 012669 0x8008C654 8FB40030 */ lw	$s4, 0X30($sp)
/* 012670 0x8008C658 8FB50034 */ lw	$s5, 0X34($sp)
/* 012671 0x8008C65C 8FB60038 */ lw	$s6, 0X38($sp)
/* 012672 0x8008C660 8FB7003C */ lw	$s7, 0X3C($sp)
/* 012673 0x8008C664 8FBE0040 */ lw	$fp, 0X40($sp)
/* 012674 0x8008C668 03E00008 */ jr	$ra
/* 012675 0x8008C66C 27BD0078 */ addiu	$sp, $sp, 0X78
