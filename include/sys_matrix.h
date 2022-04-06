#ifndef SYS_MATRIX_H
#define SYS_MATRIX_H

#include "z64.h"

/* Stack operations */
void Matrix_Init(GameState* gameState);
void Matrix_Push(void);
void Matrix_Pop(void);
void Matrix_Get(MtxF* dest);
void Matrix_Put(MtxF* src);
MtxF* Matrix_GetCurrent(void);

void Matrix_Mult(MtxF* matrix, s32 mode);
void Matrix_Translate(f32 x, f32 y, f32 z, s32 mode);
void Matrix_Scale(f32 xScale, f32 yScale, f32 zScale, s32 mode);
void Matrix_RotateXS(s16 x, s32 mode);
void Matrix_RotateXF(f32 x, s32 mode);
void Matrix_RotateXFApply(f32 x);
void Matrix_RotateXFNew(f32 x);
void Matrix_RotateYS(s16 y, s32 mode);
void Matrix_RotateYF(f32 y, s32 mode);
void Matrix_RotateZS(s16 z, s32 mode);
void Matrix_RotateZF(f32 z, s32 mode);
void Matrix_InsertRotation(s16 x, s16 y, s16 z, s32 mode);
void Matrix_JointPosition(Vec3f* pos, Vec3s* rot);
void Matrix_RotateAndTranslateState(Vec3f* translation, Vec3s* rot);
void Matrix_SetStateRotationAndTranslation(f32 x, f32 y, f32 z, Vec3s* rotation);

Mtx* Matrix_ToRSPMatrix(MtxF* src, Mtx* dest);
Mtx* Matrix_ToMtx(Mtx* dest);
Mtx* Matrix_GetStateAsRSPMatrix(Mtx* mtx);
Mtx* Matrix_NewMtx(GraphicsContext* gfxCtx);
Mtx* Matrix_AppendStateToPolyOpaDisp(GraphicsContext* gfxCtx);
Mtx* Matrix_AppendToPolyOpaDisp(MtxF* mtx, GraphicsContext* gfxCtx);

void Matrix_MultVec3f(Vec3f* src, Vec3f* dest);
void Matrix_MultZero(Vec3f* dest);
void Matrix_MultVecX(f32 x, Vec3f* dest);
void Matrix_MultVecY(f32 y, Vec3f* dest);
void Matrix_MultVecZ(f32 z, Vec3f* dest);
void Matrix_MultVec3fXZ(Vec3f* src, Vec3f* dest);
void Matrix_MtxFCopy(MtxF* dest, MtxF* src);
void Matrix_MtxToMtxF(Mtx* src, MtxF* dest);
void Matrix_MultiplyVector3fByMatrix(Vec3f* src, Vec3f* dest, MtxF* matrix);
void Matrix_TransposeXYZ(MtxF* mtx);
void Matrix_NormalizeXYZ(MtxF* mtx);
void func_8018219C(MtxF* mtx, Vec3s* rotDest, s32 flag);
void func_801822C4(MtxF* mtx, Vec3s* rotDest, s32 flag);
void Matrix_InsertRotationAroundUnitVector_f(f32 angle, Vec3f* axis, s32 mode);
void Matrix_InsertRotationAroundUnitVector_s(s16 angle, Vec3f* axis, s32 mode);

#endif
