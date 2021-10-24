#include "global.h"

void Matrix_StateAlloc(GameState* gameState) {
    sMatrixStack = (MtxF*)THA_AllocEndAlign16(&gameState->heap, 0x500);
    sCurrentMatrix = sMatrixStack;
}

void Matrix_StatePush(void) {
    MtxF* prev = sCurrentMatrix;

    sCurrentMatrix++;
    Matrix_MtxFCopy(sCurrentMatrix, prev);
}

void Matrix_StatePop(void) {
    sCurrentMatrix--;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_CopyCurrentState.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_SetCurrentState.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_GetCurrentState.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertMatrix.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertTranslation.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_Scale.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertXRotation_s.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertXRotation_f.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_RotateStateAroundXAxis.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_SetStateXRotation.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_RotateY.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertYRotation_f.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertZRotation_s.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertZRotation_f.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertRotation.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_JointPosition.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_SetStateRotationAndTranslation.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_ToRSPMatrix.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_ToMtx.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_NewMtx.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_AppendToPolyOpaDisp.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_MultiplyVector3fByState.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_GetStateTranslation.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_GetStateTranslationAndScaledX.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_GetStateTranslationAndScaledY.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_GetStateTranslationAndScaledZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_MultiplyVector3fXZByCurrentState.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_MtxFCopy.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_FromRSPMatrix.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_MultiplyVector3fByMatrix.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_TransposeXYZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_NormalizeXYZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/func_8018219C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/func_801822C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertRotationAroundUnitVector_f.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertRotationAroundUnitVector_s.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysUcode_GetUCodeBoot.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/SysUcode_GetUCodeBootSize.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/func_80182CBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/func_80182CCC.s")
