.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm


glabel __osSiCreateAccessQueue
/* 009872 0x80089AA0 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 009873 0x80089AA4 AFBF0014 */ sw	$ra, 0X14($sp)
/* 009874 0x80089AA8 240E0001 */ li	$t6, 0X1
/* 009875 0x80089AAC 3C018009 */ lui	$at, %hi(__osSiAccessQueueEnabled)
/* 009876 0x80089AB0 3C04800A */ lui	$a0, %hi(__osSiAccessQueue)
/* 009877 0x80089AB4 3C05800A */ lui	$a1, %hi(siAccessBuf)
/* 009878 0x80089AB8 AC2E7E30 */ sw	$t6, %lo(__osSiAccessQueueEnabled)($at)
/* 009879 0x80089ABC 24A5CEB0 */ addiu	$a1, $a1, %lo(siAccessBuf)
/* 009880 0x80089AC0 2484CEB8 */ addiu	$a0, $a0, %lo(__osSiAccessQueue)
/* 009881 0x80089AC4 0C023C90 */ jal	osCreateMesgQueue
/* 009882 0x80089AC8 24060001 */ li	$a2, 0X1
/* 009883 0x80089ACC 3C04800A */ lui	$a0, %hi(__osSiAccessQueue)
/* 009884 0x80089AD0 2484CEB8 */ addiu	$a0, $a0, %lo(__osSiAccessQueue)
/* 009885 0x80089AD4 00002825 */ move	$a1, $zero
/* 009886 0x80089AD8 0C021EC4 */ jal	osSendMesg
/* 009887 0x80089ADC 00003025 */ move	$a2, $zero
/* 009888 0x80089AE0 8FBF0014 */ lw	$ra, 0X14($sp)
/* 009889 0x80089AE4 27BD0018 */ addiu	$sp, $sp, 0X18
/* 009890 0x80089AE8 03E00008 */ jr	$ra
/* 009891 0x80089AEC 00000000 */ nop

glabel __osSiGetAccess
/* 009892 0x80089AF0 3C0E8009 */ lui	$t6, %hi(__osSiAccessQueueEnabled)
/* 009893 0x80089AF4 8DCE7E30 */ lw	$t6, %lo(__osSiAccessQueueEnabled)($t6)
/* 009894 0x80089AF8 27BDFFE0 */ addiu	$sp, $sp, -0X20
/* 009895 0x80089AFC AFBF0014 */ sw	$ra, 0X14($sp)
/* 009896 0x80089B00 15C00003 */ bnez	$t6, .L80089B10
/* 009897 0x80089B04 00000000 */ nop
/* 009898 0x80089B08 0C0226A8 */ jal	__osSiCreateAccessQueue
/* 009899 0x80089B0C 00000000 */ nop
.L80089B10:
/* 009900 0x80089B10 3C04800A */ lui	$a0, %hi(__osSiAccessQueue)
/* 009901 0x80089B14 2484CEB8 */ addiu	$a0, $a0, %lo(__osSiAccessQueue)
/* 009902 0x80089B18 27A5001C */ addiu	$a1, $sp, 0X1C
/* 009903 0x80089B1C 0C021FB4 */ jal	osRecvMesg
/* 009904 0x80089B20 24060001 */ li	$a2, 0X1
/* 009905 0x80089B24 8FBF0014 */ lw	$ra, 0X14($sp)
/* 009906 0x80089B28 27BD0020 */ addiu	$sp, $sp, 0X20
/* 009907 0x80089B2C 03E00008 */ jr	$ra
/* 009908 0x80089B30 00000000 */ nop

glabel __osSiRelAccess
/* 009909 0x80089B34 27BDFFE8 */ addiu	$sp, $sp, -0X18
/* 009910 0x80089B38 AFBF0014 */ sw	$ra, 0X14($sp)
/* 009911 0x80089B3C 3C04800A */ lui	$a0, %hi(__osSiAccessQueue)
/* 009912 0x80089B40 2484CEB8 */ addiu	$a0, $a0, %lo(__osSiAccessQueue)
/* 009913 0x80089B44 00002825 */ move	$a1, $zero
/* 009914 0x80089B48 0C021EC4 */ jal	osSendMesg
/* 009915 0x80089B4C 00003025 */ move	$a2, $zero
/* 009916 0x80089B50 8FBF0014 */ lw	$ra, 0X14($sp)
/* 009917 0x80089B54 27BD0018 */ addiu	$sp, $sp, 0X18
/* 009918 0x80089B58 03E00008 */ jr	$ra
/* 009919 0x80089B5C 00000000 */ nop
