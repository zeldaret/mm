#include <ultra64.h>
#include <global.h>

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

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_CopyCurrentState.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_SetCurrentState.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_GetCurrentState.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_InsertMatrix.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_InsertTranslation.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_Scale.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_InsertXRotation_s.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_InsertXRotation_f.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_RotateStateAroundXAxis.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_SetStateXRotation.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_RotateY.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_InsertYRotation_f.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_InsertZRotation_s.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_InsertZRotation_f.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_InsertRotation.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_RotateAndTranslateState.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_SetStateRotationAndTranslation.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_ToRSPMatrix.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_GetStateAsRSPMatrix.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_NewMtx.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_AppendToPolyOpaDisp.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_MultiplyVector3fByState.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_GetStateTranslation.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_GetStateTranslationAndScaledX.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_GetStateTranslationAndScaledY.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_GetStateTranslationAndScaledZ.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_MultiplyVector3fXZByCurrentState.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_MtxFCopy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_FromRSPMatrix.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_MultiplyVector3fByMatrix.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_TransposeXYZ.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_NormalizeXYZ.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/func_8018219C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/func_801822C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_InsertRotationAroundUnitVector_f.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/SysMatrix_InsertRotationAroundUnitVector_s.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/func_80182C90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/func_80182CA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/func_80182CBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/func_80182CCC.asm")
