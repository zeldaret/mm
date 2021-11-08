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

/* Stack operations */

// Matrix_Init
/* Create the matrix stack and set the pointer to the top of it */
void Matrix_StateAlloc(GameState* gameState) {
    sMatrixStack = THA_AllocEndAlign16(&gameState->heap, MATRIX_STACK_SIZE * sizeof(MtxF));
    sCurrentMatrix = sMatrixStack;
}

// Matrix_Push
/* Place a new matrix on the top of the stack */
void Matrix_StatePush(void) {
    MtxF* prev = sCurrentMatrix;

    sCurrentMatrix++;
    Matrix_MtxFCopy(sCurrentMatrix, prev);
}

// Matrix_Pop
/* Discard the top matrix on the stack */
void Matrix_StatePop(void) {
    sCurrentMatrix--;
}

// Matrix_Get
/* Read and copy the top matrix from the stack */
void Matrix_CopyCurrentState(MtxF *matrix) {
    Matrix_MtxFCopy(matrix, sCurrentMatrix);
}

// Matrix_Put
/* Write a matrix to the top of the stack */
void Matrix_SetCurrentState(MtxF *matrix) {
    Matrix_MtxFCopy(sCurrentMatrix, matrix);
}

// Matrix_GetCurrent
/* Return pointer to top of the matrix stack */
MtxF *Matrix_GetCurrentState(void) {
    return sCurrentMatrix;
}

// Matrix_Mult
void Matrix_InsertMatrix(MtxF* mf, s32 mode) {
    MtxF* cmf = Matrix_GetCurrentState();

    if (mode == MTXMODE_APPLY) {
        SkinMatrix_MtxFMtxFMult(cmf, mf, cmf);
    } else {
        Matrix_MtxFCopy(sCurrentMatrix, mf);
    }
}

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

Mtx *Matrix_ToMtx(Mtx *dest) {
    return Matrix_ToRSPMatrix(sCurrentMatrix, dest);
}

Mtx *Matrix_NewMtx(GraphicsContext *gfxCtx) {
    return Matrix_ToMtx(GRAPH_ALLOC(gfxCtx, sizeof(Mtx)));
}

// Matrix_MtxFToNewMtx
Mtx* Matrix_AppendToPolyOpaDisp(MtxF* src, GraphicsContext* gfxCtx) {
    return Matrix_ToRSPMatrix(src, GRAPH_ALLOC(gfxCtx, sizeof(Mtx)));
}

// Matrix_MultVec3f
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_MultiplyVector3fByState.s")

// Matrix_GetTranslation
// Gets the translation part of a transformation matrix
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_GetStateTranslation.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_GetStateTranslationAndScaledX.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_GetStateTranslationAndScaledY.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_GetStateTranslationAndScaledZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_MultiplyVector3fXZByCurrentState.s")

void Matrix_MtxFCopy(MtxF* dest, MtxF* src) {
    f32 f0;
    f32 f2;

    if (1) {
        f0 = src->mf[0][0];
        f2 = src->mf[0][1];
        dest->mf[0][0] = f0;
        dest->mf[0][1] = f2;
        f0 = src->mf[0][2];
        f2 = src->mf[0][3];
        dest->mf[0][2] = f0;
        dest->mf[0][3] = f2;
    }
    if (1) {
        f0 = src->mf[1][0];
        f2 = src->mf[1][1];
        dest->mf[1][0] = f0;
        dest->mf[1][1] = f2;
        f0 = src->mf[1][2];
        f2 = src->mf[1][3];
        dest->mf[1][2] = f0;
        dest->mf[1][3] = f2;
    }
    if (1) {
        f0 = src->mf[2][0];
        f2 = src->mf[2][1];
        dest->mf[2][0] = f0;
        dest->mf[2][1] = f2;
        f0 = src->mf[2][2];
        f2 = src->mf[2][3];
        dest->mf[2][2] = f0;
        dest->mf[2][3] = f2;
    }
    if (1) {
        f0 = src->mf[3][0];
        f2 = src->mf[3][1];
        dest->mf[3][0] = f0;
        dest->mf[3][1] = f2;
        f0 = src->mf[3][2];
        f2 = src->mf[3][3];
        dest->mf[3][2] = f0;
        dest->mf[3][3] = f2;
    }
}

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
