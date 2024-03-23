#ifndef SU_MTX_H
#define SU_MTX_H

#include "ultra64.h"

void Mtx_SetTranslateScaleMtx(Mtx* mtx, f32 scaleX, f32 scaleY, f32 scaleZ, f32 translateX, f32 translateY, f32 translateZ);
void Mtx_SetRotationMtx(Mtx* mtx, s32 angle, f32 axisX, f32 axisY, f32 axisZ);
void Mtx_SetTranslationRotationScaleMtx(Mtx* mtx, f32 scaleX, f32 scaleY, f32 scaleZ, s32 angle, f32 axisX, f32 axisY, f32 axisZ,f32 translateX, f32 translateY, f32 translateZ);

#endif
