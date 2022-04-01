/**
 * File: sys_matrix.c
 * Description: Matrix system that mostly uses a matrix stack.
 */
#include "global.h"

// clang-format off
Mtx gIdentityMtx = gdSPDefMtx(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
);
// clang-format on

MtxF gIdentityMtxF = { {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f },
} };

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
void Matrix_CopyCurrentState(MtxF* matrix) {
    Matrix_MtxFCopy(matrix, sCurrentMatrix);
}

// Matrix_Put
/* Write a matrix to the top of the stack */
void Matrix_SetCurrentState(MtxF* matrix) {
    Matrix_MtxFCopy(sCurrentMatrix, matrix);
}

// Matrix_GetCurrent
/* Return pointer to top of the matrix stack */
MtxF* Matrix_GetCurrentState(void) {
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
void Matrix_InsertTranslation(f32 x, f32 y, f32 z, s32 mode) {
    MtxF* cmf = sCurrentMatrix;
    f32 tx;
    f32 ty;

    if (mode == MTXMODE_APPLY) {
        tx = cmf->xx;
        ty = cmf->yx;
        cmf->wx += tx * x + ty * y + cmf->zx * z;
        tx = cmf->xy;
        ty = cmf->yy;
        cmf->wy += tx * x + ty * y + cmf->zy * z;
        tx = cmf->xz;
        ty = cmf->yz;
        cmf->wz += tx * x + ty * y + cmf->zz * z;
        tx = cmf->xw;
        ty = cmf->yw;
        cmf->ww += tx * x + ty * y + cmf->zw * z;
    } else {
        SkinMatrix_SetTranslate(cmf, x, y, z);
    }
}

void Matrix_Scale(f32 x, f32 y, f32 z, s32 mode) {
    MtxF* cmf = sCurrentMatrix;

    if (mode == MTXMODE_APPLY) {
        cmf->xx *= x;
        cmf->xy *= x;
        cmf->xz *= x;
        cmf->yx *= y;
        cmf->yy *= y;
        cmf->yz *= y;
        cmf->zx *= z;
        cmf->zy *= z;
        cmf->zz *= z;
        cmf->xw *= x;
        cmf->yw *= y;
        cmf->zw *= z;
    } else {
        SkinMatrix_SetScale(cmf, x, y, z);
    }
}

// Matrix_RotateXS
// #pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertXRotation_s.s")
void Matrix_InsertXRotation_s(s16 x, s32 mode) {
    MtxF* cmf;
    f32 sin;
    f32 cos;
    f32 temp1;
    f32 temp2;

    if (mode == MTXMODE_APPLY) {
        if (x != 0) {
            cmf = sCurrentMatrix;

            sin = Math_SinS(x);
            cos = Math_CosS(x);

            temp1 = cmf->yx;
            temp2 = cmf->zx;
            cmf->yx = temp1 * cos + temp2 * sin;
            cmf->zx = temp2 * cos - temp1 * sin;

            temp1 = cmf->yy;
            temp2 = cmf->zy;
            cmf->yy = temp1 * cos + temp2 * sin;
            cmf->zy = temp2 * cos - temp1 * sin;

            temp1 = cmf->yz;
            temp2 = cmf->zz;
            cmf->yz = temp1 * cos + temp2 * sin;
            cmf->zz = temp2 * cos - temp1 * sin;

            temp1 = cmf->yw;
            temp2 = cmf->zw;
            cmf->yw = temp1 * cos + temp2 * sin;
            cmf->zw = temp2 * cos - temp1 * sin;
        }
    } else {
        cmf = sCurrentMatrix;

        if (x != 0) {
            sin = Math_SinS(x);
            cos = Math_CosS(x);
        } else {
            sin = 0.0f;
            cos = 1.0f;
        }

        cmf->xy = 0.0f;
        cmf->xz = 0.0f;
        cmf->xw = 0.0f;
        cmf->yx = 0.0f;
        cmf->yw = 0.0f;
        cmf->zx = 0.0f;
        cmf->zw = 0.0f;
        cmf->wx = 0.0f;
        cmf->wy = 0.0f;
        cmf->wz = 0.0f;
        cmf->xx = 1.0f;
        cmf->ww = 1.0f;
        cmf->yy = cos;
        cmf->zz = cos;
        cmf->yz = sin;
        cmf->zy = -sin;
    }
}

// Matrix_RotateX
// #pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertXRotation_f.s")
void Matrix_InsertXRotation_f(f32 x, s32 mode) {
    MtxF* cmf;
    f32 sin;
    f32 cos;
    f32 temp1;
    f32 temp2;
    f32 zero = 0.0;
    f32 one = 1.0;

    if (mode == MTXMODE_APPLY) {
        if (x != 0) {
            cmf = sCurrentMatrix;

            sin = sinf(x);
            cos = cosf(x);

            temp1 = cmf->yx;
            temp2 = cmf->zx;
            cmf->yx = temp1 * cos + temp2 * sin;
            cmf->zx = temp2 * cos - temp1 * sin;

            temp1 = cmf->yy;
            temp2 = cmf->zy;
            cmf->yy = temp1 * cos + temp2 * sin;
            cmf->zy = temp2 * cos - temp1 * sin;

            temp1 = cmf->yz;
            temp2 = cmf->zz;
            cmf->yz = temp1 * cos + temp2 * sin;
            cmf->zz = temp2 * cos - temp1 * sin;

            temp1 = cmf->yw;
            temp2 = cmf->zw;
            cmf->yw = temp1 * cos + temp2 * sin;
            cmf->zw = temp2 * cos - temp1 * sin;
        }
    } else {
        cmf = sCurrentMatrix;

        if (x != 0) {
            sin = sinf(x);
            cos = cosf(x);
        } else {
            sin = zero;
            cos = one;
        }

        cmf->xx = one;
        cmf->xy = zero;
        cmf->xz = zero;
        cmf->xw = zero;
        cmf->yx = zero;
        cmf->yy = cos;
        cmf->yz = sin;
        cmf->yw = zero;
        cmf->zx = zero;
        cmf->zy = -sin;
        cmf->zz = cos;
        cmf->zw = zero;
        cmf->wx = zero;
        cmf->wy = zero;
        cmf->wz = zero;
        cmf->ww = one;
    }
}

// ?
void Matrix_RotateStateAroundXAxis(f32 x) {
    MtxF* cmf;
    f32 sin;
    f32 cos;
    f32 temp_1;
    f32 temp_2;
    s32 pad;

    if (x != 0.0f) {
        cmf = sCurrentMatrix;

        sin = sins(RADF_TO_BINANG(x)) * SHT_MINV;
        cos = coss(RADF_TO_BINANG(x)) * SHT_MINV;

        temp_1 = cmf->yx;
        temp_2 = cmf->zx;
        cmf->yx = (temp_1 * cos) + (temp_2 * sin);
        cmf->zx = (temp_2 * cos) - (temp_1 * sin);

        temp_1 = cmf->yy;
        temp_2 = cmf->zy;
        cmf->yy = (temp_1 * cos) + (temp_2 * sin);
        cmf->zy = (temp_2 * cos) - (temp_1 * sin);

        temp_1 = cmf->yz;
        temp_2 = cmf->zz;
        cmf->yz = (temp_1 * cos) + (temp_2 * sin);
        cmf->zz = (temp_2 * cos) - (temp_1 * sin);

        temp_1 = cmf->yw;
        temp_2 = cmf->zw;
        cmf->yw = (temp_1 * cos) + (temp_2 * sin);
        cmf->zw = (temp_2 * cos) - (temp_1 * sin);
    }
}

// Matrix_NewRotateX?
void Matrix_SetStateXRotation(f32 x) {
    MtxF* cmf = sCurrentMatrix;
    s32 pad;
    s32 pad1;
    f32 sin;
    f32 cos;

    cmf->xx = 1.0f;
    cmf->xy = 0.0f;
    cmf->xz = 0.0f;
    cmf->xw = 0.0f;
    cmf->yx = 0.0f;
    cmf->yw = 0.0f;
    cmf->zx = 0.0f;
    cmf->zw = 0.0f;
    cmf->wx = 0.0f;
    cmf->wy = 0.0f;
    cmf->wz = 0.0f;
    cmf->ww = 1.0f;

    if (x != 0.0f) {
        sin = sinf(x);
        cos = cosf(x);

        cmf->yy = cos;
        cmf->zz = cos;
        cmf->zy = -sin;
        cmf->yz = sin;
    } else {
        cmf->yy = 1.0f;
        cmf->yz = 0.0f;
        cmf->zy = 0.0f;
        cmf->zz = 1.0f;
    }
}

// Matrix_RotateYS?
void Matrix_RotateY(s16 y, s32 mode) {
    MtxF* cmf;
    f32 sin;
    f32 cos;
    f32 temp1;
    f32 temp2;

    if (mode == MTXMODE_APPLY) {
        if (y != 0) {
            cmf = sCurrentMatrix;

            sin = Math_SinS(y);
            cos = Math_CosS(y);

            temp1 = cmf->xx;
            temp2 = cmf->zx;
            cmf->xx = temp1 * cos - temp2 * sin;
            cmf->zx = temp1 * sin + temp2 * cos;

            temp1 = cmf->xy;
            temp2 = cmf->zy;
            cmf->xy = temp1 * cos - temp2 * sin;
            cmf->zy = temp1 * sin + temp2 * cos;

            temp1 = cmf->xz;
            temp2 = cmf->zz;
            cmf->xz = temp1 * cos - temp2 * sin;
            cmf->zz = temp1 * sin + temp2 * cos;

            temp1 = cmf->xw;
            temp2 = cmf->zw;
            cmf->xw = temp1 * cos - temp2 * sin;
            cmf->zw = temp1 * sin + temp2 * cos;
        }
    } else {
        cmf = sCurrentMatrix;

        if (y != 0) {
            sin = Math_SinS(y);
            cos = Math_CosS(y);
        } else {
            sin = 0.0f;
            cos = 1.0f;
        }

        cmf->xy = 0.0f;
        cmf->xw = 0.0f;
        cmf->yx = 0.0f;
        cmf->yz = 0.0f;
        cmf->yw = 0.0f;
        cmf->zy = 0.0f;
        cmf->zw = 0.0f;
        cmf->wx = 0.0f;
        cmf->wy = 0.0f;
        cmf->wz = 0.0f;
        cmf->yy = 1.0f;
        cmf->ww = 1.0f;
        cmf->xx = cos;
        cmf->zz = cos;
        cmf->xz = -sin;
        cmf->zx = sin;
    }
}

// Matrix_RotateY
void Matrix_InsertYRotation_f(f32 y, s32 mode) {
    MtxF* cmf;
    f32 sin;
    f32 cos;
    f32 temp1;
    f32 temp2;
    f32 zero = 0.0;
    f32 one = 1.0;

    if (mode == MTXMODE_APPLY) {
        if (y != 0.0f) {
            cmf = sCurrentMatrix;

            sin = sinf(y);
            cos = cosf(y);

            temp1 = cmf->xx;
            temp2 = cmf->zx;
            cmf->xx = temp1 * cos - temp2 * sin;
            cmf->zx = temp1 * sin + temp2 * cos;

            temp1 = cmf->xy;
            temp2 = cmf->zy;
            cmf->xy = temp1 * cos - temp2 * sin;
            cmf->zy = temp1 * sin + temp2 * cos;

            temp1 = cmf->xz;
            temp2 = cmf->zz;
            cmf->xz = temp1 * cos - temp2 * sin;
            cmf->zz = temp1 * sin + temp2 * cos;

            temp1 = cmf->xw;
            temp2 = cmf->zw;
            cmf->xw = temp1 * cos - temp2 * sin;
            cmf->zw = temp1 * sin + temp2 * cos;
        }
    } else {
        cmf = sCurrentMatrix;

        if (y != 0.0f) {
            sin = sinf(y);
            cos = cosf(y);
        } else {
            cos = one;
            sin = zero;
        }

        cmf->xy = zero;
        cmf->xw = zero;
        cmf->yx = zero;
        cmf->yz = zero;
        cmf->yw = zero;
        cmf->zy = zero;
        cmf->zw = zero;
        cmf->wx = zero;
        cmf->wy = zero;
        cmf->wz = zero;
        cmf->yy = one;
        cmf->ww = one;
        cmf->xx = cos;
        cmf->zz = cos;
        cmf->xz = -sin;
        cmf->zx = sin;
    }
}

// Matrix_RotateZS
// #pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertZRotation_s.s")
void Matrix_InsertZRotation_s(s16 z, s32 mode) {
    MtxF* cmf;
    f32 sin;
    f32 cos;
    f32 temp1;
    f32 temp2;
    f32 zero = 0.0;
    f32 one = 1.0;

    if (mode == MTXMODE_APPLY) {
        if (z != 0) {
            cmf = sCurrentMatrix;

            sin = Math_SinS(z);
            cos = Math_CosS(z);

            temp1 = cmf->xx;
            temp2 = cmf->yx;
            cmf->xx = temp1 * cos + temp2 * sin;
            cmf->yx = temp2 * cos - temp1 * sin;

            temp1 = cmf->xy;
            temp2 = cmf->yy;
            cmf->xy = temp1 * cos + temp2 * sin;
            cmf->yy = temp2 * cos - temp1 * sin;

            temp1 = cmf->xz;
            temp2 = cmf->yz;
            cmf->xz = temp1 * cos + temp2 * sin;
            cmf->yz = temp2 * cos - temp1 * sin;

            temp1 = cmf->xw;
            temp2 = cmf->yw;
            cmf->xw = temp1 * cos + temp2 * sin;
            cmf->yw = temp2 * cos - temp1 * sin;
        }
    } else {
        cmf = sCurrentMatrix;

        if (z != 0) {
            sin = Math_SinS(z);
            cos = Math_CosS(z);
        } else {
            sin = zero;
            cos = one;
        }

        cmf->xz = zero;
        cmf->xw = zero;
        cmf->yz = zero;
        cmf->yw = zero;
        cmf->zx = zero;
        cmf->zy = zero;
        cmf->zw = zero;
        cmf->wx = zero;
        cmf->wy = zero;
        cmf->wz = zero;
        cmf->zz = one;
        cmf->ww = one;
        cmf->xx = cos;
        cmf->yy = cos;
        cmf->xy = sin;
        cmf->yx = -sin;
    }
}

// Matrix_RotateZ
void Matrix_InsertZRotation_f(f32 z, s32 mode) {
    MtxF* cmf;
    f32 sin;
    f32 cos;
    f32 temp1;
    f32 temp2;

    if (mode == MTXMODE_APPLY) {
        if (z != 0) {
            cmf = sCurrentMatrix;

            sin = sinf(z);
            cos = cosf(z);

            temp1 = cmf->xx;
            temp2 = cmf->yx;
            cmf->xx = temp1 * cos + temp2 * sin;
            cmf->yx = temp2 * cos - temp1 * sin;

            temp1 = cmf->xy;
            temp2 = cmf->yy;
            cmf->xy = temp1 * cos + temp2 * sin;
            cmf->yy = temp2 * cos - temp1 * sin;

            temp1 = cmf->xz;
            temp2 = cmf->yz;
            cmf->xz = temp1 * cos + temp2 * sin;
            cmf->yz = temp2 * cos - temp1 * sin;

            temp1 = cmf->xw;
            temp2 = cmf->yw;
            cmf->xw = temp1 * cos + temp2 * sin;
            cmf->yw = temp2 * cos - temp1 * sin;
        }
    } else {
        cmf = sCurrentMatrix;

        if (z != 0) {
            sin = sinf(z);
            cos = cosf(z);
        } else {
            sin = 0.0f;
            cos = 1.0f;
        }

        cmf->xz = 0.0f;
        cmf->xw = 0.0f;
        cmf->yz = 0.0f;
        cmf->yw = 0.0f;
        cmf->zx = 0.0f;
        cmf->zy = 0.0f;
        cmf->zw = 0.0f;
        cmf->wx = 0.0f;
        cmf->wy = 0.0f;
        cmf->wz = 0.0f;
        cmf->zz = 1.0f;
        cmf->ww = 1.0f;
        cmf->xx = cos;
        cmf->yy = cos;
        cmf->xy = sin;
        cmf->yx = -sin;
    }
}

// Matrix_RotateZYX
// #pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_InsertRotation.s")
void Matrix_InsertRotation(s16 x, s16 y, s16 z, s32 mode) {
    MtxF* cmf = sCurrentMatrix;
    f32 temp1;
    f32 temp2;
    f32 sin;
    f32 cos;

    if (mode == MTXMODE_APPLY) {
        if (z != 0) {
            sin = Math_SinS(z);
            cos = Math_CosS(z);

            temp1 = cmf->xx;
            temp2 = cmf->yx;
            cmf->xx = temp1 * cos + temp2 * sin;
            cmf->yx = temp2 * cos - temp1 * sin;

            temp1 = cmf->xy;
            temp2 = cmf->yy;
            cmf->xy = temp1 * cos + temp2 * sin;
            cmf->yy = temp2 * cos - temp1 * sin;

            temp1 = cmf->xz;
            temp2 = cmf->yz;
            cmf->xz = temp1 * cos + temp2 * sin;
            cmf->yz = temp2 * cos - temp1 * sin;

            temp1 = cmf->xw;
            temp2 = cmf->yw;
            cmf->xw = temp1 * cos + temp2 * sin;
            cmf->yw = temp2 * cos - temp1 * sin;
        }

        if (y != 0) {
            sin = Math_SinS(y);
            cos = Math_CosS(y);

            temp1 = cmf->xx;
            temp2 = cmf->zx;
            cmf->xx = temp1 * cos - temp2 * sin;
            cmf->zx = temp1 * sin + temp2 * cos;

            temp1 = cmf->xy;
            temp2 = cmf->zy;
            cmf->xy = temp1 * cos - temp2 * sin;
            cmf->zy = temp1 * sin + temp2 * cos;

            temp1 = cmf->xz;
            temp2 = cmf->zz;
            cmf->xz = temp1 * cos - temp2 * sin;
            cmf->zz = temp1 * sin + temp2 * cos;

            temp1 = cmf->xw;
            temp2 = cmf->zw;
            cmf->xw = temp1 * cos - temp2 * sin;
            cmf->zw = temp1 * sin + temp2 * cos;
        }

        if (x != 0) {
            sin = Math_SinS(x);
            cos = Math_CosS(x);

            temp1 = cmf->yx;
            temp2 = cmf->zx;
            cmf->yx = temp1 * cos + temp2 * sin;
            cmf->zx = temp2 * cos - temp1 * sin;

            temp1 = cmf->yy;
            temp2 = cmf->zy;
            cmf->yy = temp1 * cos + temp2 * sin;
            cmf->zy = temp2 * cos - temp1 * sin;

            temp1 = cmf->yz;
            temp2 = cmf->zz;
            cmf->yz = temp1 * cos + temp2 * sin;
            cmf->zz = temp2 * cos - temp1 * sin;

            temp1 = cmf->yw;
            temp2 = cmf->zw;
            cmf->yw = temp1 * cos + temp2 * sin;
            cmf->zw = temp2 * cos - temp1 * sin;
        }
    } else {
        SkinMatrix_SetRotateRPY(cmf, x, y, z);
    }
}

// Matrix_TranslateRotateZYX
// #pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_JointPosition.s")
void Matrix_JointPosition(Vec3f* translation, Vec3s* rotation) {
    MtxF* cmf = sCurrentMatrix;
    f32 sin = Math_SinS(rotation->z);
    f32 cos = Math_CosS(rotation->z);
    f32 temp1;
    f32 temp2;

    temp1 = cmf->xx;
    temp2 = cmf->yx;
    cmf->wx += temp1 * translation->x + temp2 * translation->y + cmf->zx * translation->z;
    cmf->xx = temp1 * cos + temp2 * sin;
    cmf->yx = temp2 * cos - temp1 * sin;

    temp1 = cmf->xy;
    temp2 = cmf->yy;
    cmf->wy += temp1 * translation->x + temp2 * translation->y + cmf->zy * translation->z;
    cmf->xy = temp1 * cos + temp2 * sin;
    cmf->yy = temp2 * cos - temp1 * sin;

    temp1 = cmf->xz;
    temp2 = cmf->yz;
    cmf->wz += temp1 * translation->x + temp2 * translation->y + cmf->zz * translation->z;
    cmf->xz = temp1 * cos + temp2 * sin;
    cmf->yz = temp2 * cos - temp1 * sin;

    temp1 = cmf->xw;
    temp2 = cmf->yw;
    cmf->ww += temp1 * translation->x + temp2 * translation->y + cmf->zw * translation->z;
    cmf->xw = temp1 * cos + temp2 * sin;
    cmf->yw = temp2 * cos - temp1 * sin;

    if (rotation->y != 0) {
        sin = Math_SinS(rotation->y);
        cos = Math_CosS(rotation->y);

        temp1 = cmf->xx;
        temp2 = cmf->zx;
        cmf->xx = temp1 * cos - temp2 * sin;
        cmf->zx = temp1 * sin + temp2 * cos;

        temp1 = cmf->xy;
        temp2 = cmf->zy;
        cmf->xy = temp1 * cos - temp2 * sin;
        cmf->zy = temp1 * sin + temp2 * cos;

        temp1 = cmf->xz;
        temp2 = cmf->zz;
        cmf->xz = temp1 * cos - temp2 * sin;
        cmf->zz = temp1 * sin + temp2 * cos;

        temp1 = cmf->xw;
        temp2 = cmf->zw;
        cmf->xw = temp1 * cos - temp2 * sin;
        cmf->zw = temp1 * sin + temp2 * cos;
    }

    if (rotation->x != 0) {
        sin = Math_SinS(rotation->x);
        cos = Math_CosS(rotation->x);

        temp1 = cmf->yx;
        temp2 = cmf->zx;
        cmf->yx = temp1 * cos + temp2 * sin;
        cmf->zx = temp2 * cos - temp1 * sin;

        temp1 = cmf->yy;
        temp2 = cmf->zy;
        cmf->yy = temp1 * cos + temp2 * sin;
        cmf->zy = temp2 * cos - temp1 * sin;

        temp1 = cmf->yz;
        temp2 = cmf->zz;
        cmf->yz = temp1 * cos + temp2 * sin;
        cmf->zz = temp2 * cos - temp1 * sin;

        temp1 = cmf->yw;
        temp2 = cmf->zw;
        cmf->yw = temp1 * cos + temp2 * sin;
        cmf->zw = temp2 * cos - temp1 * sin;
    }
}

// Matrix_SetTranslateRotateYXZ
void Matrix_SetStateRotationAndTranslation(f32 x, f32 y, f32 z, Vec3s* vec) {
    MtxF* cmf = sCurrentMatrix;
    f32 sp30 = Math_SinS(vec->y);
    f32 sp2C = Math_CosS(vec->y);
    f32 sp28;
    f32 sp24;

    cmf->xx = sp2C;
    cmf->xz = -sp30;
    cmf->wx = x;
    cmf->wy = y;
    cmf->wz = z;
    cmf->xw = 0.0f;
    cmf->yw = 0.0f;
    cmf->zw = 0.0f;
    cmf->ww = 1.0f;

    if (vec->x != 0) {
        sp24 = Math_SinS(vec->x);
        sp28 = Math_CosS(vec->x);

        cmf->zz = sp2C * sp28;
        cmf->yz = sp2C * sp24;
        cmf->zx = sp30 * sp28;
        cmf->yx = sp30 * sp24;
        cmf->zy = -sp24;
        cmf->yy = sp28;
    } else {
        cmf->zz = sp2C;
        cmf->zx = sp30;
        cmf->zy = 0.0f;
        cmf->yz = 0.0f;
        cmf->yx = 0.0f;
        cmf->yy = 1.0f;
    }

    if (vec->z != 0) {
        sp24 = Math_SinS(vec->z);
        sp28 = Math_CosS(vec->z);

        sp30 = cmf->xx;
        sp2C = cmf->yx;
        cmf->xx = sp30 * sp28 + sp2C * sp24;
        cmf->yx = sp2C * sp28 - sp30 * sp24;

        sp30 = cmf->xz;
        sp2C = cmf->yz;
        cmf->xz = sp30 * sp28 + sp2C * sp24;
        cmf->yz = sp2C * sp28 - sp30 * sp24;

        sp2C = cmf->yy;
        cmf->xy = sp2C * sp24;
        cmf->yy = sp2C * sp28;
    } else {
        cmf->xy = 0.0f;
    }
}

// Matrix_MtxFToMtx
// #pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_ToRSPMatrix.s")
Mtx* Matrix_ToRSPMatrix(MtxF* src, Mtx* dest) {
    s32 temp;
    u16* mInt = (u16*)&dest->m[0][0];
    u16* mFrac = (u16*)&dest->m[2][0];

    temp = src->xx * 0x10000;
    mInt[0] = (temp >> 0x10);
    mInt[16 + 0] = temp;

    temp = src->xy * 0x10000;
    mInt[1] = (temp >> 0x10);
    mInt[16 + 1] = temp;

    temp = src->xz * 0x10000;
    mInt[2] = (temp >> 0x10);
    mInt[16 + 2] = temp;

    temp = src->xw * 0x10000;
    mInt[3] = (temp >> 0x10);
    mInt[16 + 3] = temp;

    temp = src->yx * 0x10000;
    mInt[4] = (temp >> 0x10);
    mInt[16 + 4] = temp;

    temp = src->yy * 0x10000;
    mInt[5] = (temp >> 0x10);
    mInt[16 + 5] = temp;

    temp = src->yz * 0x10000;
    mInt[6] = (temp >> 0x10);
    mInt[16 + 6] = temp;

    temp = src->yw * 0x10000;
    mInt[7] = (temp >> 0x10);
    mInt[16 + 7] = temp;

    temp = src->zx * 0x10000;
    mInt[8] = (temp >> 0x10);
    mInt[16 + 8] = temp;

    temp = src->zy * 0x10000;
    mInt[9] = (temp >> 0x10);
    mFrac[9] = temp;

    temp = src->zz * 0x10000;
    mInt[10] = (temp >> 0x10);
    mFrac[10] = temp;

    temp = src->zw * 0x10000;
    mInt[11] = (temp >> 0x10);
    mFrac[11] = temp;

    temp = src->wx * 0x10000;
    mInt[12] = (temp >> 0x10);
    mFrac[12] = temp;

    temp = src->wy * 0x10000;
    mInt[13] = (temp >> 0x10);
    mFrac[13] = temp;

    temp = src->wz * 0x10000;
    mInt[14] = (temp >> 0x10);
    mFrac[14] = temp;

    temp = src->ww * 0x10000;
    mInt[15] = (temp >> 0x10);
    mFrac[15] = temp;

    return dest;
}

Mtx* Matrix_ToMtx(Mtx* dest) {
    return Matrix_ToRSPMatrix(sCurrentMatrix, dest);
}

Mtx* Matrix_NewMtx(GraphicsContext* gfxCtx) {
    return Matrix_ToMtx(GRAPH_ALLOC(gfxCtx, sizeof(Mtx)));
}

// Matrix_MtxFToNewMtx
Mtx* Matrix_AppendToPolyOpaDisp(MtxF* src, GraphicsContext* gfxCtx) {
    return Matrix_ToRSPMatrix(src, GRAPH_ALLOC(gfxCtx, sizeof(Mtx)));
}

// Matrix_MultVec3f
// #pragma GLOBAL_ASM("asm/non_matchings/code/sys_matrix/Matrix_MultiplyVector3fByState.s")
void Matrix_MultiplyVector3fByState(Vec3f* src, Vec3f* dest) {
    MtxF* cmf = sCurrentMatrix;

    dest->x = cmf->wx + (cmf->xx * src->x + cmf->yx * src->y + cmf->zx * src->z);
    dest->y = cmf->wy + (cmf->xy * src->x + cmf->yy * src->y + cmf->zy * src->z);
    dest->z = cmf->wz + (cmf->xz * src->x + cmf->yz * src->y + cmf->zz * src->z);
}

// Matrix_GetTranslation
// Gets the translation part of a transformation matrix
void Matrix_GetStateTranslation(Vec3f* translateOut) {
    MtxF* cmf = sCurrentMatrix;

    translateOut->x = cmf->wx;
    translateOut->y = cmf->wy;
    translateOut->z = cmf->wz;
}

// Matrix_MultX
void Matrix_GetStateTranslationAndScaledX(f32 arg0, Vec3f* dst) {
    MtxF* cmf = sCurrentMatrix;

    dst->x = cmf->wx + cmf->xx * arg0;
    dst->y = cmf->wy + cmf->xy * arg0;
    dst->z = cmf->wz + cmf->xz * arg0;
}

// Matrix_MultY
void Matrix_GetStateTranslationAndScaledY(f32 arg0, Vec3f* dst) {
    MtxF* cmf = sCurrentMatrix;

    dst->x = cmf->wx + cmf->yx * arg0;
    dst->y = cmf->wy + cmf->yy * arg0;
    dst->z = cmf->wz + cmf->yz * arg0;
}

// Matrix_MultZ
void Matrix_GetStateTranslationAndScaledZ(f32 arg0, Vec3f* dst) {
    MtxF* cmf = sCurrentMatrix;

    dst->x = cmf->wx + cmf->zx * arg0;
    dst->y = cmf->wy + cmf->zy * arg0;
    dst->z = cmf->wz + cmf->zz * arg0;
}

// Matrix_MultVec3fXZ
void Matrix_MultiplyVector3fXZByCurrentState(Vec3f* arg0, Vec3f* dst) {
    MtxF* cmf = sCurrentMatrix;

    dst->x = cmf->wx + (cmf->xx * arg0->x + cmf->yx * arg0->y + cmf->zx * arg0->z);
    dst->z = cmf->wz + (cmf->xz * arg0->x + cmf->yz * arg0->y + cmf->zz * arg0->z);
}

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
/**
 * @brief Converts fixed-point
 *
 * @param src
 * @param dest
 */
void Matrix_FromRSPMatrix(Mtx* src, MtxF* dest) {
    u16* mInt = (u16*)&src->m[0][0];
    u16* mFrac = (u16*)&src->m[2][0];

    dest->xx = ((mInt[0] << 0x10) | mFrac[0]) * (1 / (f32)0x10000);
    dest->xy = ((mInt[1] << 0x10) | mFrac[1]) * (1 / (f32)0x10000);
    dest->xz = ((mInt[2] << 0x10) | mFrac[2]) * (1 / (f32)0x10000);
    dest->xw = ((mInt[3] << 0x10) | mFrac[3]) * (1 / (f32)0x10000);
    dest->yx = ((mInt[4] << 0x10) | mFrac[4]) * (1 / (f32)0x10000);
    dest->yy = ((mInt[5] << 0x10) | mFrac[5]) * (1 / (f32)0x10000);
    dest->yz = ((mInt[6] << 0x10) | mFrac[6]) * (1 / (f32)0x10000);
    dest->yw = ((mInt[7] << 0x10) | mFrac[7]) * (1 / (f32)0x10000);
    dest->zx = ((mInt[8] << 0x10) | mFrac[8]) * (1 / (f32)0x10000);
    dest->zy = ((mInt[9] << 0x10) | mFrac[9]) * (1 / (f32)0x10000);
    dest->zz = ((mInt[10] << 0x10) | mFrac[10]) * (1 / (f32)0x10000);
    dest->zw = ((mInt[11] << 0x10) | mFrac[11]) * (1 / (f32)0x10000);
    dest->wx = ((mInt[12] << 0x10) | mFrac[12]) * (1 / (f32)0x10000);
    dest->wy = ((mInt[13] << 0x10) | mFrac[13]) * (1 / (f32)0x10000);
    dest->wz = ((mInt[14] << 0x10) | mFrac[14]) * (1 / (f32)0x10000);
    dest->ww = ((mInt[15] << 0x10) | mFrac[15]) * (1 / (f32)0x10000);
}

// Matrix_MultVec3fExt
void Matrix_MultiplyVector3fByMatrix(Vec3f* src, Vec3f* dest, MtxF* mf) {
    dest->x = mf->wx + (mf->xx * src->x + mf->yx * src->y + mf->zx * src->z);
    dest->y = mf->wy + (mf->xy * src->x + mf->yy * src->y + mf->zy * src->z);
    dest->z = mf->wz + (mf->xz * src->x + mf->yz * src->y + mf->zz * src->z);
}

// Matrix_Transpose or Matrix_Reverse
void Matrix_TransposeXYZ(MtxF* mf) {
    f32 temp;

    temp = mf->xy;
    mf->xy = mf->yx;
    mf->yx = temp;

    temp = mf->xz;
    mf->xz = mf->zx;
    mf->zx = temp;

    temp = mf->yz;
    mf->yz = mf->zy;
    mf->zy = temp;
}

// Matrix_ReplaceRotation
void Matrix_NormalizeXYZ(MtxF* mf) {
    MtxF* cmf = sCurrentMatrix;
    f32 temp;
    f32 temp2;
    f32 temp3;

    temp = cmf->xx;
    temp *= temp;
    temp2 = cmf->xy;
    temp += SQ(temp2);
    temp2 = cmf->xz;
    temp += SQ(temp2);
    temp3 = sqrtf(temp);

    cmf->xx = mf->xx * temp3;
    cmf->xy = mf->xy * temp3;
    cmf->xz = mf->xz * temp3;

    temp = cmf->yx;
    temp *= temp;
    temp2 = cmf->yy;
    temp += SQ(temp2);
    temp2 = cmf->yz;
    temp += SQ(temp2);
    temp3 = sqrtf(temp);

    cmf->yx = mf->yx * temp3;
    cmf->yy = mf->yy * temp3;
    cmf->yz = mf->yz * temp3;

    temp = cmf->zx;
    temp *= temp;
    temp2 = cmf->zy;
    temp += SQ(temp2);
    temp2 = cmf->zz;
    temp += SQ(temp2);
    temp3 = sqrtf(temp);

    cmf->zx = mf->zx * temp3;
    cmf->zy = mf->zy * temp3;
    cmf->zz = mf->zz * temp3;
}

// Matrix_MtxFToYXZRotS
void func_8018219C(MtxF* mf, Vec3s* rotDest, s32 flag) {
    f32 temp;
    f32 temp2;
    f32 temp3;
    f32 temp4;

    temp = mf->zx;
    temp *= temp;
    temp += SQ(mf->zz);
    rotDest->x = Math_Atan2S(-mf->zy, sqrtf(temp));

    if ((rotDest->x == 0x4000) || (rotDest->x == -0x4000)) {
        rotDest->z = 0;

        rotDest->y = Math_Atan2S(-mf->xz, mf->xx);
    } else {
        rotDest->y = Math_Atan2S(mf->zx, mf->zz);

        if (!flag) {
            rotDest->z = Math_Atan2S(mf->xy, mf->yy);
        } else {
            temp = mf->xx;
            temp2 = mf->xz;
            temp3 = mf->yz;

            temp *= temp;
            temp += SQ(temp2);
            temp2 = mf->xy;
            temp += SQ(temp2);
            temp = sqrtf(temp);
            temp = temp2 / temp;

            temp2 = mf->yx;
            temp2 *= temp2;
            temp2 += SQ(temp3);
            temp3 = mf->yy;
            temp2 += SQ(temp3);
            temp2 = sqrtf(temp2);
            temp2 = temp3 / temp2;

            rotDest->z = Math_Atan2S(temp, temp2);
        }
    }
}

// Matrix_MtxFToZYXRotS
void func_801822C4(MtxF* mf, Vec3s* rotDest, s32 flag) {
    f32 temp;
    f32 temp2;
    f32 temp3;
    f32 temp4;

    temp = mf->xx;
    temp *= temp;
    temp += SQ(mf->xy);
    rotDest->y = Math_Atan2S(-mf->xz, sqrtf(temp));

    if ((rotDest->y == 0x4000) || (rotDest->y == -0x4000)) {
        rotDest->x = 0;
        rotDest->z = Math_Atan2S(-mf->yx, mf->yy);
        return;
    }

    rotDest->z = Math_Atan2S(mf->xy, mf->xx);

    if (!flag) {
        rotDest->x = Math_Atan2S(mf->yz, mf->zz);
    } else {
        temp = mf->yx;
        temp2 = mf->yy;
        temp3 = mf->zy;

        temp *= temp;
        temp += SQ(temp2);
        temp2 = mf->yz;
        temp += SQ(temp2);
        temp = sqrtf(temp);
        temp = temp2 / temp;

        temp2 = mf->zx;
        temp2 *= temp2;
        temp2 += SQ(temp3);
        temp3 = mf->zz;
        temp2 += SQ(temp3);
        temp2 = sqrtf(temp2);
        temp2 = temp3 / temp2;

        rotDest->x = Math_Atan2S(temp, temp2);
    }
}

// Matrix_RotateAxisF
void Matrix_InsertRotationAroundUnitVector_f(f32 angle, Vec3f* axis, s32 mode) {
    MtxF* cmf;
    f32 sin;
    f32 cos;
    f32 rCos;
    f32 vrs;
    f32 temp1;
    f32 temp2;
    f32 temp3;
    f32 temp4;
    f32 temp5;

    if (mode == MTXMODE_APPLY) {
        if (angle != 0) {
            cmf = sCurrentMatrix;

            sin = sinf(angle);
            cos = cosf(angle);

            temp2 = cmf->yx;
            temp3 = cmf->zx;
            temp1 = cmf->xx;
            temp4 = (axis->x * temp1 + axis->y * temp2 + axis->z * temp3) * (1.0f - cos);
            cmf->xx = temp1 * cos + axis->x * temp4 + sin * (temp2 * axis->z - temp3 * axis->y);
            cmf->yx = temp2 * cos + axis->y * temp4 + sin * (temp3 * axis->x - temp1 * axis->z);
            cmf->zx = temp3 * cos + axis->z * temp4 + sin * (temp1 * axis->y - temp2 * axis->x);

            temp1 = cmf->xy;
            temp2 = cmf->yy;
            temp3 = cmf->zy;
            temp4 = (axis->x * temp1 + axis->y * temp2 + axis->z * temp3) * (1.0f - cos);
            cmf->xy = temp1 * cos + axis->x * temp4 + sin * (temp2 * axis->z - temp3 * axis->y);
            cmf->yy = temp2 * cos + axis->y * temp4 + sin * (temp3 * axis->x - temp1 * axis->z);
            cmf->zy = temp3 * cos + axis->z * temp4 + sin * (temp1 * axis->y - temp2 * axis->x);

            temp1 = cmf->xz;
            temp2 = cmf->yz;
            temp3 = cmf->zz;
            temp4 = (axis->x * temp1 + axis->y * temp2 + axis->z * temp3) * (1.0f - cos);
            cmf->xz = temp1 * cos + axis->x * temp4 + sin * (temp2 * axis->z - temp3 * axis->y);
            cmf->yz = temp2 * cos + axis->y * temp4 + sin * (temp3 * axis->x - temp1 * axis->z);
            cmf->zz = temp3 * cos + axis->z * temp4 + sin * (temp1 * axis->y - temp2 * axis->x);
        }
    } else {
        cmf = sCurrentMatrix;

        if (angle != 0) {
            sin = sinf(angle);
            cos = cosf(angle);
            rCos = 1.0f - cos;

            cmf->xx = axis->x * axis->x * rCos + cos;
            cmf->yy = axis->y * axis->y * rCos + cos;
            cmf->zz = axis->z * axis->z * rCos + cos;

            if (0) {}

            temp2 = axis->x * rCos * axis->y;
            temp3 = axis->z * sin;
            cmf->xy = temp2 + temp3;
            cmf->yx = temp2 - temp3;

            temp2 = axis->x * rCos * axis->z;
            temp3 = axis->y * sin;
            cmf->xz = temp2 - temp3;
            cmf->zx = temp2 + temp3;

            temp2 = axis->y * rCos * axis->z;
            temp3 = axis->x * sin;
            cmf->yz = temp2 + temp3;
            cmf->zy = temp2 - temp3;

            cmf->xw = cmf->yw = cmf->zw = cmf->wx = cmf->wy = cmf->wz = 0.0f;
            cmf->ww = 1.0f;
        } else {
            cmf->xy = 0.0f;
            cmf->xz = 0.0f;
            cmf->xw = 0.0f;
            cmf->yx = 0.0f;
            cmf->yz = 0.0f;
            cmf->yw = 0.0f;
            cmf->zx = 0.0f;
            cmf->zy = 0.0f;
            cmf->zw = 0.0f;
            cmf->wx = 0.0f;
            cmf->wy = 0.0f;
            cmf->wz = 0.0f;
            cmf->xx = 1.0f;
            cmf->yy = 1.0f;
            cmf->zz = 1.0f;
            cmf->ww = 1.0f;
        }
    }
}

// Matrix_RotateAxisS
void Matrix_InsertRotationAroundUnitVector_s(s16 angle, Vec3f* axis, s32 mode) {
    MtxF* cmf;
    f32 cos;
    f32 sin;
    f32 rCos;
    f32 temp1;
    f32 temp2;
    f32 temp3;
    f32 temp4;

    if (mode == MTXMODE_APPLY) {
        if (angle != 0) {
            cmf = sCurrentMatrix;

            sin = Math_SinS(angle);
            cos = Math_CosS(angle);

            temp2 = cmf->yx;
            temp3 = cmf->zx;
            temp1 = cmf->xx;
            temp4 = (axis->x * temp1 + axis->y * temp2 + axis->z * temp3) * (1.0f - cos);
            cmf->xx = temp1 * cos + axis->x * temp4 + sin * (temp2 * axis->z - temp3 * axis->y);
            cmf->yx = temp2 * cos + axis->y * temp4 + sin * (temp3 * axis->x - temp1 * axis->z);
            cmf->zx = temp3 * cos + axis->z * temp4 + sin * (temp1 * axis->y - temp2 * axis->x);

            temp1 = cmf->xy;
            temp2 = cmf->yy;
            temp3 = cmf->zy;
            temp4 = (axis->x * temp1 + axis->y * temp2 + axis->z * temp3) * (1.0f - cos);
            cmf->xy = temp1 * cos + axis->x * temp4 + sin * (temp2 * axis->z - temp3 * axis->y);
            cmf->yy = temp2 * cos + axis->y * temp4 + sin * (temp3 * axis->x - temp1 * axis->z);
            cmf->zy = temp3 * cos + axis->z * temp4 + sin * (temp1 * axis->y - temp2 * axis->x);

            temp1 = cmf->xz;
            temp2 = cmf->yz;
            temp3 = cmf->zz;
            temp4 = (axis->x * temp1 + axis->y * temp2 + axis->z * temp3) * (1.0f - cos);
            cmf->xz = temp1 * cos + axis->x * temp4 + sin * (temp2 * axis->z - temp3 * axis->y);
            cmf->yz = temp2 * cos + axis->y * temp4 + sin * (temp3 * axis->x - temp1 * axis->z);
            cmf->zz = temp3 * cos + axis->z * temp4 + sin * (temp1 * axis->y - temp2 * axis->x);
        }
    } else {
        cmf = sCurrentMatrix;

        if (angle != 0) {
            sin = Math_SinS(angle);
            cos = Math_CosS(angle);
            rCos = 1.0f - cos;

            cmf->xx = axis->x * axis->x * rCos + cos;
            cmf->yy = axis->y * axis->y * rCos + cos;
            cmf->zz = axis->z * axis->z * rCos + cos;

            if (0) {}

            temp2 = axis->x * rCos * axis->y;
            temp3 = axis->z * sin;
            cmf->xy = temp2 + temp3;
            cmf->yx = temp2 - temp3;

            temp2 = axis->x * rCos * axis->z;
            temp3 = axis->y * sin;
            cmf->xz = temp2 - temp3;
            cmf->zx = temp2 + temp3;

            temp2 = axis->y * rCos * axis->z;
            temp3 = axis->x * sin;
            cmf->yz = temp2 + temp3;
            cmf->zy = temp2 - temp3;

            cmf->xw = cmf->yw = cmf->zw = cmf->wx = cmf->wy = cmf->wz = 0.0f;
            cmf->ww = 1.0f;
        } else {
            cmf->xy = 0.0f;
            cmf->xz = 0.0f;
            cmf->xw = 0.0f;
            cmf->yx = 0.0f;
            cmf->yz = 0.0f;
            cmf->yw = 0.0f;
            cmf->zx = 0.0f;
            cmf->zy = 0.0f;
            cmf->zw = 0.0f;
            cmf->wx = 0.0f;
            cmf->wy = 0.0f;
            cmf->wz = 0.0f;
            cmf->xx = 1.0f;
            cmf->yy = 1.0f;
            cmf->zz = 1.0f;
            cmf->ww = 1.0f;
        }
    }
}
