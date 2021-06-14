#include "ultra64.h"
#include "global.h"

#include "z_camera_data.c"

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_fabsf.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_LengthVec3f.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB270.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Lerpf.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Lerps.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB42C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_LerpVec3f.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB544.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB584.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB5DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB60C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB674.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB6C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB700.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB780.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB7CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB7F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB828.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB854.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB880.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB8C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB8F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB924.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CB950.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CBA08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CBA34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CBA7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CBAAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CBAD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CBB58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CBB88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CBC00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CBC30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CBC84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CBFA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC000.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC128.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC1C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC260.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC488.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC56C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC5C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC740.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC7A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC804.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC874.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC938.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC958.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CC9C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CCCEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD04C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD288.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD2E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD2F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD3E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD44C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD6CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD6F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CD834.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CDA14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CDB6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CDE6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CE2B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CE5E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CE79C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CE930.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CEAD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CEC38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800CED90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeNop.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeNORM1.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeNORM2.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeNORM3.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeNORM4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeNORM0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModePARA1.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModePARA2.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModePARA3.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModePARA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModePARA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeJUMP1.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeJUMP2.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeJUMP3.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeJUMP4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeJUMP0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeBATT1.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeBATT2.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeBATT3.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeBATT4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeBATT0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeKEEP1.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeKEEP2.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeKEEP3.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeKEEP4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeKEEP0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeFIXD1.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeFIXD2.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeFIXD3.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeFIXD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeFIXD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeSUBJ1.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeSUBJ2.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeSUBJ3.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeSUBJ4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeSUBJ0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeDATA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeDATA1.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeDATA2.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeDATA3.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeDATA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeUNIQ1.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeUNIQ2.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeUNIQ3.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeUNIQ4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeUNIQ5.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeUNIQ0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeUNIQ6.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeUNIQ7.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeUNIQ8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeUNIQ9.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeDEMO1.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeDEMO2.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeDEMO3.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeDEMO4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeDEMO5.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeDEMO6.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeDEMO7.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeDEMO8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeDEMO9.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeDEMO0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeSPEC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeSPEC1.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeSPEC2.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeSPEC3.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeSPEC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeSPEC5.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeSPEC6.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeSPEC7.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeSPEC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ModeSPEC9.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Alloc.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Free.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DDFE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DE0E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DE0EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DE308.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DE324.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DE62C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DE840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DE890.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DE954.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DF498.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_SetMode.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DF840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DF86C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DF8EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFAC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFB14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFC1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFC40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFC68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFC90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFCB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFCDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFD04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFD78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFEF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFF18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFF34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFF44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_SetFlags.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/Camera_ClearFlags.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800DFFAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E007C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E01AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E01B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E01DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E0228.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E0238.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E02AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E0308.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E031C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_camera/func_800E0348.asm")

