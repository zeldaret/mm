glabel Fault_Start
/* 003801 0x80083BC4 3C08FFFA */ lui	$t0, 0xFFFA
/* 003802 0x80083BC8 03A04825 */ move	$t1, $sp
/* 003803 0x80083BCC 27BDFFD8 */ addiu	$sp, $sp, -0X28
/* 003804 0x80083BD0 35085A5A */ ori	$t0, $t0, 0X5A5A
.L80083BD4:
/* 003805 0x80083BD4 2529FFF8 */ addiu	$t1, $t1, -0X8
/* 003806 0x80083BD8 AD280000 */ sw	$t0, 0X0($t1)
/* 003807 0x80083BDC 153DFFFD */ bne	$t1, $sp, .L80083BD4
/* 003808 0x80083BE0 AD280004 */ sw	$t0, 0X4($t1)
/* 003809 0x80083BE4 AFB00020 */ sw	$s0, 0X20($sp)
/* 003810 0x80083BE8 3C10800A */ lui	$s0, %hi(faultCtxt)
/* 003811 0x80083BEC 2610BE50 */ addiu	$s0, $s0, %lo(faultCtxt)
/* 003812 0x80083BF0 AFBF0024 */ sw	$ra, 0X24($sp)
/* 003813 0x80083BF4 3C0E800A */ lui	$t6, %hi(faultContextStruct)
/* 003814 0x80083BF8 25C4C480 */ addiu	$a0, $t6, %lo(faultContextStruct)
/* 003815 0x80083BFC AE040000 */ sw	$a0, 0X0($s0)
/* 003816 0x80083C00 0C02258C */ jal	bzero
/* 003817 0x80083C04 24050848 */ li	$a1, 0X848
/* 003818 0x80083C08 0C02122E */ jal	FaultDrawer_Init
/* 003819 0x80083C0C 00000000 */ nop
/* 003820 0x80083C10 3C048008 */ lui	$a0, %hi(Fault_WaitForInput)
/* 003821 0x80083C14 0C021229 */ jal	FaultDrawer_SetInputCallback
/* 003822 0x80083C18 2484203C */ addiu	$a0, $a0, %lo(Fault_WaitForInput)
/* 003823 0x80083C1C 8E0F0000 */ lw	$t7, 0X0($s0)
/* 003824 0x80083C20 3C098008 */ lui	$t1, %hi(Fault_PadCallback)
/* 003825 0x80083C24 25291E68 */ addiu	$t1, $t1, %lo(Fault_PadCallback)
/* 003826 0x80083C28 A1E007CC */ sb	$zero, 0X7CC($t7)
/* 003827 0x80083C2C 8E180000 */ lw	$t8, 0X0($s0)
/* 003828 0x80083C30 240D0001 */ li	$t5, 0X1
/* 003829 0x80083C34 3C01800A */ lui	$at, %hi(faultContextStruct + 0x7CE)
/* 003830 0x80083C38 A30007CD */ sb	$zero, 0X7CD($t8)
/* 003831 0x80083C3C 8E190000 */ lw	$t9, 0X0($s0)
/* 003832 0x80083C40 24060001 */ li	$a2, 0X1
/* 003833 0x80083C44 A32007CE */ sb	$zero, 0X7CE($t9)
/* 003834 0x80083C48 8E080000 */ lw	$t0, 0X0($s0)
/* 003835 0x80083C4C AD0007D0 */ sw	$zero, 0X7D0($t0)
/* 003836 0x80083C50 8E0A0000 */ lw	$t2, 0X0($s0)
/* 003837 0x80083C54 AD4907D4 */ sw	$t1, 0X7D4($t2)
/* 003838 0x80083C58 8E0B0000 */ lw	$t3, 0X0($s0)
/* 003839 0x80083C5C AD6007D8 */ sw	$zero, 0X7D8($t3)
/* 003840 0x80083C60 8E0C0000 */ lw	$t4, 0X0($s0)
/* 003841 0x80083C64 A18007CF */ sb	$zero, 0X7CF($t4)
/* 003842 0x80083C68 A02DCC4E */ sb	$t5, %lo(faultContextStruct + 0x7CE)($at)
/* 003843 0x80083C6C 8E020000 */ lw	$v0, 0X0($s0)
/* 003844 0x80083C70 244407B0 */ addiu	$a0, $v0, 0X7B0
/* 003845 0x80083C74 0C023C90 */ jal	osCreateMesgQueue
/* 003846 0x80083C78 244507C8 */ addiu	$a1, $v0, 0X7C8
/* 003847 0x80083C7C 3C0F800A */ lui	$t7, %hi(faultThreadName)
/* 003848 0x80083C80 25EF8BD8 */ addiu	$t7, $t7, %lo(faultThreadName)
/* 003849 0x80083C84 3C04800A */ lui	$a0, %hi(faultStackEntry)
/* 003850 0x80083C88 3C05800A */ lui	$a1, %hi(faultStack)
/* 003851 0x80083C8C 3C06800A */ lui	$a2, %hi(faultStackEntry)
/* 003852 0x80083C90 240E0100 */ li	$t6, 0X100
/* 003853 0x80083C94 AFAE0010 */ sw	$t6, 0X10($sp)
/* 003854 0x80083C98 24C6C460 */ addiu	$a2, $a2, %lo(faultStackEntry)
/* 003855 0x80083C9C 24A5BE60 */ addiu	$a1, $a1, %lo(faultStack)
/* 003856 0x80083CA0 2484C460 */ addiu	$a0, $a0, %lo(faultStackEntry)
/* 003857 0x80083CA4 AFAF0014 */ sw	$t7, 0X14($sp)
/* 003858 0x80083CA8 0C0214C8 */ jal	StackCheck_Init
/* 003859 0x80083CAC 00003825 */ move	$a3, $zero
/* 003860 0x80083CB0 3C18800A */ lui	$t8, %hi(faultStackEntry)
/* 003861 0x80083CB4 2718C460 */ addiu	$t8, $t8, %lo(faultStackEntry)
/* 003862 0x80083CB8 3C068008 */ lui	$a2, %hi(Fault_ThreadEntry)
/* 003863 0x80083CBC 2419007F */ li	$t9, 0X7F
/* 003864 0x80083CC0 AFB90014 */ sw	$t9, 0X14($sp)
/* 003865 0x80083CC4 24C63828 */ addiu	$a2, $a2, %lo(Fault_ThreadEntry)
/* 003866 0x80083CC8 AFB80010 */ sw	$t8, 0X10($sp)
/* 003867 0x80083CCC 8E040000 */ lw	$a0, 0X0($s0)
/* 003868 0x80083CD0 24050002 */ li	$a1, 0X2
/* 003869 0x80083CD4 0C022790 */ jal	osCreateThread
/* 003870 0x80083CD8 00003825 */ move	$a3, $zero
/* 003871 0x80083CDC 0C0255EC */ jal	osStartThread
/* 003872 0x80083CE0 8E040000 */ lw	$a0, 0X0($s0)
/* 003873 0x80083CE4 8FBF0024 */ lw	$ra, 0X24($sp)
/* 003874 0x80083CE8 8FB00020 */ lw	$s0, 0X20($sp)
/* 003875 0x80083CEC 27BD0028 */ addiu	$sp, $sp, 0X28
/* 003876 0x80083CF0 03E00008 */ jr	$ra
/* 003877 0x80083CF4 00000000 */ nop

