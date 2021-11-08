/**
 * File: sys_matrix.c
 * Description: Matrix system that mostly uses a matrix stack.
 */
#include "global.h"

// clang-format off
// Mtx gMtxClear = gdSPDefMtx(
Mtx gIdentityMtx = gdSPDefMtx(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
);

// MtxF gMtxFClear = {
MtxF gIdentityMtxF = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};
// clang-format on

MtxF* sMatrixStack;   // "Matrix_stack"
MtxF* sCurrentMatrix; // "Matrix_now"

#define MATRIX_STACK_SIZE 20

// Matrix_Init
void Matrix_StateAlloc(GameState* gameState) {
    sMatrixStack = THA_AllocEndAlign16(&gameState->heap, MATRIX_STACK_SIZE * sizeof(MtxF));
    sCurrentMatrix = sMatrixStack;
}

// Matrix_Push
void Matrix_StatePush(void) {
    MtxF* prev = sCurrentMatrix;

    sCurrentMatrix++;
    Matrix_MtxFCopy(sCurrentMatrix, prev);
}

// Matrix_Pop
void Matrix_StatePop(void) {
    sCurrentMatrix--;
}

// Matrix_Get
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_CopyCurrentState.s")

// Matrix_Push
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_SetCurrentState.s")

// Matrix_GetCurrent
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_GetCurrentState.s")

// Matrix_Mult
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertMatrix.s")

// Matrix_Translate
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertTranslation.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_Scale.s")

// Matrix_RotateX
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertXRotation_s.s")

// Matrix_RotateXF
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertXRotation_f.s")


#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_RotateStateAroundXAxis.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_SetStateXRotation.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_RotateY.s")

// Matrix_RotateYF
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertYRotation_f.s")

// Matrix_RotateZ
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertZRotation_s.s")

// Matrix_RotateZF
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertZRotation_f.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertRotation.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_JointPosition.s")

// Matrix_RotateRPY
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_SetStateRotationAndTranslation.s")

// Matrix_MtxFToMtx
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_ToRSPMatrix.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_ToMtx.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_NewMtx.s")

// Matrix_MtxFToNewMtx
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_AppendToPolyOpaDisp.s")

// Matrix_MultVec3f
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_MultiplyVector3fByState.s")

// Matrix_GetTranslation
// Gets the translation part of a transformation matrix
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_GetStateTranslation.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_GetStateTranslationAndScaledX.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_GetStateTranslationAndScaledY.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_GetStateTranslationAndScaledZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_MultiplyVector3fXZByCurrentState.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_MtxFCopy.s")

// Matrix_MtxToMtxF
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_FromRSPMatrix.s")

// Matrix_MultVec3fExt
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_MultiplyVector3fByMatrix.s")

// Matrix_Reverse
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_TransposeXYZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_NormalizeXYZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/func_8018219C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/func_801822C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertRotationAroundUnitVector_f.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertRotationAroundUnitVector_s.s")
