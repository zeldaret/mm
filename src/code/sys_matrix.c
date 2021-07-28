#include "global.h"

void SysMatrix_StateAlloc(GameState* gamestate) {
    sMatrixStack = (MtxF*)THA_AllocEndAlign16(&gamestate->heap, 0x500);
    sCurrentMatrix = sMatrixStack;
}

void SysMatrix_StatePush(void) {
    MtxF* prev = sCurrentMatrix;

    sCurrentMatrix++;
    Matrix_MtxFCopy(sCurrentMatrix, prev);
}

void SysMatrix_StatePop(void) {
    sCurrentMatrix--;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_CopyCurrentState.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_SetCurrentState.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_GetCurrentState.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_InsertMatrix.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_InsertTranslation.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_Scale.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_InsertXRotation_s.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_InsertXRotation_f.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_RotateStateAroundXAxis.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_SetStateXRotation.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_RotateY.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_InsertYRotation_f.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_InsertZRotation_s.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_InsertZRotation_f.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_InsertRotation.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_RotateAndTranslateState.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_SetStateRotationAndTranslation.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_ToRSPMatrix.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_GetStateAsRSPMatrix.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_NewMtx.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_AppendToPolyOpaDisp.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_MultiplyVector3fByState.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_GetStateTranslation.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_GetStateTranslationAndScaledX.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_GetStateTranslationAndScaledY.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_GetStateTranslationAndScaledZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_MultiplyVector3fXZByCurrentState.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_MtxFCopy.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_FromRSPMatrix.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_MultiplyVector3fByMatrix.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_TransposeXYZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_NormalizeXYZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/func_8018219C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/func_801822C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_InsertRotationAroundUnitVector_f.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysMatrix_InsertRotationAroundUnitVector_s.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/func_80182C90.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/func_80182CA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/func_80182CBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/func_80182CCC.s")
