glabel Dmamgr_Start
/* 000811 0x80080D0C 27BDFFE0 */ addiu	$sp, $sp, -0X20
/* 000812 0x80080D10 AFBF001C */ sw	$ra, 0X1C($sp)
/* 000813 0x80080D14 3C040002 */ lui	$a0, 0x0002
/* 000814 0x80080D18 3C0E0002 */ lui	$t6, 0x0002
/* 000815 0x80080D1C 25CE0700 */ addiu	$t6, $t6, 0X700
/* 000816 0x80080D20 2484A500 */ addiu	$a0, $a0, -0X5B00
/* 000817 0x80080D24 3C05800A */ lui	$a1, %hi(dmadata)
/* 000818 0x80080D28 24A5F8B0 */ addiu	$a1, $a1, %lo(dmadata)
/* 000819 0x80080D2C 0C0201E4 */ jal	DmaMgr_DMARomToRam
/* 000820 0x80080D30 01C43023 */ subu	$a2, $t6, $a0
/* 000821 0x80080D34 3C04800A */ lui	$a0, %hi(dmadata)
/* 000822 0x80080D38 2484F8B0 */ addiu	$a0, $a0, %lo(dmadata)
/* 000823 0x80080D3C 8C8F0004 */ lw	$t7, 0X4($a0)
/* 000824 0x80080D40 00801025 */ move	$v0, $a0
/* 000825 0x80080D44 00001825 */ move	$v1, $zero
/* 000826 0x80080D48 11E00006 */ beqz	$t7, .L80080D64
/* 000827 0x80080D4C 3C01800A */ lui	$at, %hi(numDmaEntries)
/* 000828 0x80080D50 8C580014 */ lw	$t8, 0X14($v0)
.L80080D54:
/* 000829 0x80080D54 24420010 */ addiu	$v0, $v0, 0X10
/* 000830 0x80080D58 24630001 */ addiu	$v1, $v1, 0X1
/* 000831 0x80080D5C 5700FFFD */ bnezl	$t8, .L80080D54
/* 000832 0x80080D60 8C580014 */ lw	$t8, 0X14($v0)
.L80080D64:
/* 000833 0x80080D64 A423B2BC */ sh	$v1, %lo(numDmaEntries)($at)
/* 000834 0x80080D68 3C04800A */ lui	$a0, %hi(dmamgrMsq)
/* 000835 0x80080D6C 3C05800A */ lui	$a1, %hi(dmamgrMsqMessages)
/* 000836 0x80080D70 24A5B2D8 */ addiu	$a1, $a1, %lo(dmamgrMsqMessages)
/* 000837 0x80080D74 2484B2C0 */ addiu	$a0, $a0, %lo(dmamgrMsq)
/* 000838 0x80080D78 0C023C90 */ jal	osCreateMesgQueue
/* 000839 0x80080D7C 24060020 */ li	$a2, 0X20
/* 000840 0x80080D80 3C08800A */ lui	$t0, %hi(dmamgrThreadName)
/* 000841 0x80080D84 25088204 */ addiu	$t0, $t0, %lo(dmamgrThreadName)
/* 000842 0x80080D88 3C04800A */ lui	$a0, %hi(dmamgrStackEntry)
/* 000843 0x80080D8C 3C05800A */ lui	$a1, %hi(dmamgrStack)
/* 000844 0x80080D90 3C06800A */ lui	$a2, %hi(D_8009BA08)
/* 000845 0x80080D94 24190100 */ li	$t9, 0X100
/* 000846 0x80080D98 AFB90010 */ sw	$t9, 0X10($sp)
/* 000847 0x80080D9C 24C6BA08 */ addiu	$a2, $a2, %lo(D_8009BA08)
/* 000848 0x80080DA0 24A5B508 */ addiu	$a1, $a1, %lo(dmamgrStack)
/* 000849 0x80080DA4 2484B2A0 */ addiu	$a0, $a0, %lo(dmamgrStackEntry)
/* 000850 0x80080DA8 AFA80014 */ sw	$t0, 0X14($sp)
/* 000851 0x80080DAC 0C0214C8 */ jal	StackCheck_Init
/* 000852 0x80080DB0 00003825 */ move	$a3, $zero
/* 000853 0x80080DB4 3C09800A */ lui	$t1, %hi(D_8009BA08)
/* 000854 0x80080DB8 2529BA08 */ addiu	$t1, $t1, %lo(D_8009BA08)
/* 000855 0x80080DBC 3C04800A */ lui	$a0, %hi(dmamgrOSThread)
/* 000856 0x80080DC0 3C068008 */ lui	$a2, %hi(Dmamgr_ThreadEntry)
/* 000857 0x80080DC4 240A0011 */ li	$t2, 0X11
/* 000858 0x80080DC8 AFAA0014 */ sw	$t2, 0X14($sp)
/* 000859 0x80080DCC 24C60B84 */ addiu	$a2, $a2, %lo(Dmamgr_ThreadEntry)
/* 000860 0x80080DD0 2484B358 */ addiu	$a0, $a0, %lo(dmamgrOSThread)
/* 000861 0x80080DD4 AFA90010 */ sw	$t1, 0X10($sp)
/* 000862 0x80080DD8 24050012 */ li	$a1, 0X12
/* 000863 0x80080DDC 0C022790 */ jal	osCreateThread
/* 000864 0x80080DE0 00003825 */ move	$a3, $zero
/* 000865 0x80080DE4 3C04800A */ lui	$a0, %hi(dmamgrOSThread)
/* 000866 0x80080DE8 0C0255EC */ jal	osStartThread
/* 000867 0x80080DEC 2484B358 */ addiu	$a0, $a0, %lo(dmamgrOSThread)
/* 000868 0x80080DF0 8FBF001C */ lw	$ra, 0X1C($sp)
/* 000869 0x80080DF4 27BD0020 */ addiu	$sp, $sp, 0X20
/* 000870 0x80080DF8 03E00008 */ jr	$ra
/* 000871 0x80080DFC 00000000 */ nop

