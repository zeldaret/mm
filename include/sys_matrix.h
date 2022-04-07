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
void Matrix_RotateZYX(s16 x, s16 y, s16 z, s32 mode);
void Matrix_TranslateRotateZYX(Vec3f* pos, Vec3s* rot);
void Matrix_RotateAndTranslateState(Vec3f* translation, Vec3s* rot);
void Matrix_SetTranslateRotateYXZ(f32 x, f32 y, f32 z, Vec3s* rotation);

Mtx* Matrix_MtxFToMtx(MtxF* src, Mtx* dest);
Mtx* Matrix_ToMtx(Mtx* dest);
Mtx* Matrix_NewMtx(GraphicsContext* gfxCtx);
Mtx* Matrix_MtxFToNewMtx(MtxF* mtx, GraphicsContext* gfxCtx);

void Matrix_MultVec3f(Vec3f* src, Vec3f* dest);
void Matrix_MultZero(Vec3f* dest);
void Matrix_MultVecX(f32 x, Vec3f* dest);
void Matrix_MultVecY(f32 y, Vec3f* dest);
void Matrix_MultVecZ(f32 z, Vec3f* dest);
void Matrix_MultVec3fXZ(Vec3f* src, Vec3f* dest);
void Matrix_MtxFCopy(MtxF* dest, MtxF* src);
void Matrix_MtxToMtxF(Mtx* src, MtxF* dest);
void Matrix_MultVec3fExt(Vec3f* src, Vec3f* dest, MtxF* matrix);
void Matrix_Transpose(MtxF* mtx);
void Matrix_ReplaceRotation(MtxF* mtx);
void Matrix_MtxFToYXZRot(MtxF* mtx, Vec3s* rotDest, s32 flag);
void Matrix_MtxFToZYXRot(MtxF* mtx, Vec3s* rotDest, s32 flag);
void Matrix_RotateAxisF(f32 angle, Vec3f* axis, s32 mode);
void Matrix_RotateAxisS(s16 angle, Vec3f* axis, s32 mode);

#endif
