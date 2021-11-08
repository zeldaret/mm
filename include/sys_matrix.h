#ifndef SYS_MATRIX
#define SYS_MATRIX

#include "z64.h"

void Matrix_StateAlloc(GameState* gameState);
void Matrix_StatePush(void);
void Matrix_StatePop(void);
void Matrix_CopyCurrentState(MtxF* matrix);
void Matrix_SetCurrentState(MtxF* matrix);
MtxF* Matrix_GetCurrentState(void);
void Matrix_InsertMatrix(MtxF* matrix, s32 appendToState);
void Matrix_InsertTranslation(f32 x, f32 y, f32 z, s32 appendToState);
void Matrix_Scale(f32 xScale, f32 yScale, f32 zScale, s32 appendToState);
void Matrix_InsertXRotation_s(s16 rotation, s32 appendToState);
void Matrix_InsertXRotation_f(f32 rotation, s32 appendToState);
void Matrix_RotateStateAroundXAxis(f32 rotation);
void Matrix_SetStateXRotation(f32 rotation);
void Matrix_RotateY(s16 rotation, s32 appendToState);
void Matrix_InsertYRotation_f(f32 rotation, s32 appendToState);
void Matrix_InsertZRotation_s(s16 rotation, s32 appendToState);
void Matrix_InsertZRotation_f(f32 rotation, s32 appendToState);
void Matrix_InsertRotation(s16 xRotation, s16 yRotation, s16 zRotation, s32 appendToState);
void Matrix_JointPosition(Vec3f* position, Vec3s* rotation);
void Matrix_RotateAndTranslateState(Vec3f* translation, Vec3s* rotation);
void Matrix_SetStateRotationAndTranslation(f32 x, f32 y, f32 z, Vec3s* rotation);
Mtx* Matrix_ToRSPMatrix(MtxF* src, Mtx* dest);
Mtx* Matrix_ToMtx(Mtx* dest);
Mtx* Matrix_GetStateAsRSPMatrix(Mtx* matrix);
Mtx* Matrix_NewMtx(GraphicsContext* gfxCtx);
Mtx* Matrix_AppendStateToPolyOpaDisp(GraphicsContext* gfxCtx);
Mtx* Matrix_AppendToPolyOpaDisp(MtxF* mtx, GraphicsContext* gfxCtx);
void Matrix_MultiplyVector3fByState(Vec3f* src, Vec3f* dst);
void Matrix_GetStateTranslation(Vec3f* dst);
void Matrix_GetStateTranslationAndScaledX(f32 scale, Vec3f* dst);
void Matrix_GetStateTranslationAndScaledY(f32 scale, Vec3f* dst);
void Matrix_GetStateTranslationAndScaledZ(f32 scale, Vec3f* dst);
void Matrix_MultiplyVector3fXZByCurrentState(Vec3f* src, Vec3f* dst);
void Matrix_MtxFCopy(MtxF* dst, MtxF* src);
void Matrix_FromRSPMatrix(Mtx* src, MtxF* dst);
void Matrix_MultiplyVector3fByMatrix(Vec3f* src, Vec3f* dst, MtxF* matrix);
void Matrix_TransposeXYZ(MtxF* matrix);
void Matrix_NormalizeXYZ(MtxF* matrix);
void func_8018219C(MtxF* pfParm1, Vec3s* psParm2, s32 iParm3);
// void func_801822C4(void);
void Matrix_InsertRotationAroundUnitVector_f(f32 rotation, Vec3f* vector, s32 appendToState);
void Matrix_InsertRotationAroundUnitVector_s(s16 rotation, Vec3f* vector, s32 appendToState);

#endif
