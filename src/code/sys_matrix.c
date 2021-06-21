#include <ultra64.h>
#include <global.h>

void Matrix_StateAlloc(GameState* gamestate) {
    sMatrixStack = (MtxF*)THA_AllocEndAlign16(&gamestate->heap, 0x500);
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

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_CopyCurrentState.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_SetCurrentState.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_GetCurrentState.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_InsertMatrix.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_InsertTranslation.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_Scale.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_InsertXRotation_s.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_InsertXRotation_f.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_RotateStateAroundXAxis.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_SetStateXRotation.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_RotateY.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_InsertYRotation_f.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_InsertZRotation_s.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_InsertZRotation_f.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_InsertRotation.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_JointPosition.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_SetStateRotationAndTranslation.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_ToRSPMatrix.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_ToMtx.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_NewMtx.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_AppendToPolyOpaDisp.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_MultiplyVector3fByState.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_GetStateTranslation.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_GetStateTranslationAndScaledX.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_GetStateTranslationAndScaledY.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_GetStateTranslationAndScaledZ.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_MultiplyVector3fXZByCurrentState.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_MtxFCopy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_FromRSPMatrix.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_MultiplyVector3fByMatrix.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_TransposeXYZ.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_NormalizeXYZ.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/func_8018219C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/func_801822C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_InsertRotationAroundUnitVector_f.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/Matrix_InsertRotationAroundUnitVector_s.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/func_80182C90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/func_80182CA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/func_80182CBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/sys_matrix/func_80182CCC.asm")
