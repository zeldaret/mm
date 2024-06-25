#ifndef Z64OLIB_H
#define Z64OLIB_H

#include "ultra64.h"

#include "z64math.h"

// To be used with OLib_Vec3fAdd()
typedef enum {
    /* 0 */ OLIB_ADD_COPY, // Copy `b` to dest
    /* 1 */ OLIB_ADD_OFFSET, // Add `a` and `b` to dest, and also add the yaw of `a` to the dest
    /* 2 */ OLIB_ADD // Add `a` and `b` to dest
} OlibVec3fAdd;

typedef enum {
    /* 0 */ OLIB_DIFF_COPY, // Copy `b` to dest
    /* 1 */ OLIB_DIFF_OFFSET, // Sub `a` and `b` to dest, and also subs the yaw of `a` to the dest
    /* 2 */ OLIB_DIFF // Sub `a` and `b` to dest
} OlibVec3fDiff;

f32 OLib_Vec3fDist(Vec3f* a, Vec3f* b);
f32 OLib_Vec3fDistOutDiff(Vec3f* a, Vec3f* b, Vec3f* dest);
f32 OLib_Vec3fDistXZ(Vec3f* a, Vec3f* b);
f32 OLib_ClampMinDist(f32 val, f32 min);
f32 OLib_ClampMaxDist(f32 val, f32 max);
Vec3f OLib_Vec3fDistNormalize(Vec3f* a, Vec3f* b);
Vec3f OLib_VecSphToVec3f(VecSph* sph);
Vec3f OLib_VecGeoToVec3f(VecGeo* geo);
VecSph OLib_Vec3fToVecSph(Vec3f* vec);
VecGeo OLib_Vec3fToVecGeo(Vec3f* vec);
VecSph OLib_Vec3fDiffToVecSph(Vec3f* a, Vec3f* b);
VecGeo OLib_Vec3fDiffToVecGeo(Vec3f* a, Vec3f* b);
Vec3f OLib_AddVecGeoToVec3f(Vec3f* a, VecGeo* geo);
Vec3f OLib_Vec3fDiffRad(Vec3f* a, Vec3f* b);
Vec3f OLib_Vec3fDiffDegF(Vec3f* a, Vec3f* b);
Vec3s OLib_Vec3fDiffBinAng(Vec3f* a, Vec3f* b);
void OLib_Vec3fDiff(PosRot* a, Vec3f* b, Vec3f* dest, s16 mode);
void OLib_Vec3fAdd(PosRot* a, Vec3f* b, Vec3f* dest, s16 mode);

#endif
