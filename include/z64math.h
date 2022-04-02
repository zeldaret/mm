#ifndef Z64MATH_H
#define Z64MATH_H

#include "PR/ultratypes.h"

#define VEC_SET(V,X,Y,Z) V.x=X;V.y=Y;V.z=Z

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 z;
} Vec2s; // size = 0x04

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 z;
} Vec2f; // size = 0x08

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Vec3f; // size = 0x0C

typedef struct {
    /* 0x00 */ u16 x;
    /* 0x02 */ u16 y;
    /* 0x04 */ u16 z;
} Vec3us; // size = 0x06

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
} Vec3s; // size = 0x06

typedef struct {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 z;
} Vec3i; // size = 0x0C

typedef struct {
    /* 0x00 */ Vec3s center;
    /* 0x06 */ s16   radius;
} Sphere16; // size = 0x08

typedef struct {
    /* 0x00 */ Vec3f center;
    /* 0x0C */ f32   radius;
} Spheref; // size = 0x10

typedef struct {
    /* 0x00 */ Vec3f normal;
    /* 0x0C */ f32   originDist;
} Plane; // size = 0x10

typedef struct {
    /* 0x00 */ Vec3f vtx[3];
    /* 0x24 */ Plane plane;
} TriNorm; // size = 0x34

typedef struct {
    /* 0x00 */ s16   radius;
    /* 0x02 */ s16   height;
    /* 0x04 */ s16   yShift;
    /* 0x06 */ Vec3s pos;
} Cylinder16; // size = 0x0C

typedef struct {
    /* 0x00 */ f32   radius;
    /* 0x04 */ f32   height;
    /* 0x08 */ f32   yShift;
    /* 0x0C */ Vec3f pos;
} Cylinderf; // size = 0x18

typedef struct {
    /* 0x00 */ Vec3f point;
    /* 0x0C */ Vec3f dir;
} InfiniteLine; // size = 0x18

typedef struct {
    /* 0x00 */ Vec3f a;
    /* 0x0C */ Vec3f b;
} Linef; // size = 0x18

// Defines a point in the spherical coordinate system
typedef struct {
    /* 0x00 */ f32 r;       // radius
    /* 0x04 */ s16 pitch;   // polar (zenith) angle
    /* 0x06 */ s16 yaw;     // azimuthal angle
} VecSph; // size = 0x08

#define LERPIMP(v0, v1, t) ((v0) + (((v1) - (v0)) * (t)))
#define F32_LERP(v0, v1, t) ((1.0f - (t)) * (f32)(v0) + (t) * (f32)(v1))
#define F32_LERPIMP(v0, v1, t) ((f32)(v0) + (((f32)(v1) - (f32)(v0)) * (t)))
#define F32_LERPIMPINV(v0, v1, t) ((f32)(v0) + (((f32)(v1) - (f32)(v0)) / (t)))
#define BINANG_LERPIMP(v0, v1, t) ((v0) + (s16)(BINANG_SUB((v1), (v0)) * (t)))
#define BINANG_LERPIMPINV(v0, v1, t) ((v0) + BINANG_SUB((v1), (v0)) / (t))

#define VEC3F_LERPIMPDST(dst, v0, v1, t){ \
    (dst)->x = (v0)->x + (((v1)->x - (v0)->x) * t); \
    (dst)->y = (v0)->y + (((v1)->y - (v0)->y) * t); \
    (dst)->z = (v0)->z + (((v1)->z - (v0)->z) * t); \
}

#define IS_ZERO(f) (fabsf(f) < 0.008f)

#define SQ(x) ((x) * (x))
#define ABS(x) ((x) >= 0 ? (x) : -(x))
#define ABS_ALT(x) ((x) < 0 ? -(x) : (x))

// Trig macros
#define DEGF_TO_BINANG(degreesf) (s16)(degreesf * 182.04167f + .5f)
#define RADF_TO_BINANG(radf) (s16)(radf * (32768.0f / M_PI))
#define RADF_TO_DEGF(radf) (radf * (180.0f / M_PI))
#define DEGF_TO_RADF(degf) (degf * (M_PI / 180.0f))
#define BINANG_ROT180(angle) ((s16)(angle + 0x8000))
#define BINANG_SUB(a, b) ((s16)(a - b))
#define BINANG_ADD(a, b) ((s16)(a + b))
#define DEG_TO_RAD(degrees) ((degrees) * (M_PI / 180.0f))
#define BINANG_TO_DEGF(binang) ((f32)binang * (360.0001525f / 65535.0f))
#define BINANG_TO_RAD(binang) (((f32)binang / 32768.0f) * M_PI)

// Vector macros
#define SQXZ(vec) ((vec.x) * (vec.x) + (vec.z) * (vec.z))
#define DOTXZ(vec1, vec2) ((vec1.x) * (vec2.x) + (vec1.z) * (vec2.z))
#define SQXYZ(vec) ((vec.x) * (vec.x) + (vec.y) * (vec.y) + (vec.z) * (vec.z))
#define DOTXYZ(vec1, vec2) ((vec1.x) * (vec2.x) + (vec1.y) * (vec2.y) + (vec1.z) * (vec2.z))


f32 Math_CosS(s16 angle);
f32 Math_SinS(s16 angle);
s32 Math_StepToIImpl(s32 start, s32 target, s32 step);
void Math_StepToIGet(s32* pValue, s32 target, s32 step);
s32 Math_StepToI(s32* pValue, s32 target, s32 step);
s32 Math_ScaledStepToS(s16* pValue, s16 target, s16 step);
s32 Math_StepToS(s16* pValue, s16 target, s16 step);
s32 Math_StepToC(s8* pValue, s8 target, s8 step);
s32 Math_StepToF(f32* pValue, f32 target, f32 step);
s32 Math_StepUntilAngleS(s16* pValue, s16 target, s16 step);
s32 Math_StepToAngleS(s16* pValue, s16 target, s16 step);
s32 Math_AsymStepToS(s16* pValue, s16 target, s16 incrStep, s16 decrStep);
s32 Math_StepUntilF(f32* pValue, f32 limit, f32 step);
s32 Math_AsymStepToF(f32* pValue, f32 target, f32 incrStep, f32 decrStep);
void Math_Vec3f_Copy(Vec3f* dest, Vec3f* src);
void Math_Vec3s_Copy(Vec3s* dest, Vec3s* src);
void Math_Vec3s_ToVec3f(Vec3f* dest, Vec3s* src);
void Math_Vec3f_ToVec3s(Vec3s* dest, Vec3f* src);
void Math_Vec3f_Sum(Vec3f* l, Vec3f* r, Vec3f* dest);
void Math_Vec3f_Diff(Vec3f* l, Vec3f* r, Vec3f* dest);
void Math_Vec3s_DiffToVec3f(Vec3f* dest, Vec3s* l, Vec3s* r);
void Math_Vec3f_Scale(Vec3f* vec, f32 scale);
void Math_Vec3f_ScaleAndStore(Vec3f* vec, f32 scale, Vec3f* dest);
void Math_Vec3f_Lerp(Vec3f* a, Vec3f* b, f32 t, Vec3f* dest);
void Math_Vec3f_SumScaled(Vec3f* a, Vec3f* b, f32 scale, Vec3f* dest);
void Math_Vec3f_AddRand(Vec3f* orig, f32 scale, Vec3f* dest);
void Math_Vec3f_DistXYZAndStoreNormDiff(Vec3f* a, Vec3f* b, f32 scale, Vec3f* dest);
f32 Math_Vec3f_DistXYZ(Vec3f* a, Vec3f* b);
f32 Math_Vec3f_DistXYZAndStoreDiff(Vec3f* a, Vec3f* b, Vec3f* dest);
f32 Math_Vec3f_DistXZ(Vec3f* a, Vec3f* b);
f32 Math_Vec3f_DistXZAndStore(Vec3f* a, Vec3f* b, f32* dx, f32* dz);
f32 Math_Vec3f_StepToXZ(Vec3f* start, Vec3f* target, f32 speed);
f32 Math_Vec3f_DiffY(Vec3f* a, Vec3f* b);
s16 Math_Vec3f_Yaw(Vec3f* a, Vec3f* b);
s16 Math_Vec3f_Pitch(Vec3f* a, Vec3f* b);
f32 Math_SmoothStepToF(f32* pValue, f32 target, f32 fraction, f32 step, f32 minStep);
void Math_ApproachF(f32* pValue, f32 target, f32 scale, f32 maxStep);
void Math_ApproachZeroF(f32* pValue, f32 scale, f32 maxStep);
s16 Math_SmoothStepToS(s16* pValue, s16 target, s16 scale, s16 step, s16 minStep);
void Math_ApproachS(s16* pValue, s16 target, s16 scale, s16 maxStep);
f32 Math_Vec3f_StepTo(Vec3f* start, Vec3f* target, f32 speed);

u16 Math_GetAtan2Tbl(f32 opposite, f32 adjacent);
s16 Math_Atan2S(f32 opposite, f32 adjacent);
f32 Math_Atan2F(f32 opposite, f32 adjacent);
s16 Math_FAtan2F(f32 adjacent, f32 opposite);
f32 Math_Acot2F(f32 adjacent, f32 opposite);

f32 Math3D_Normalize(Vec3f* vec);
s32 Math3D_PlaneVsLineSegClosestPoint(f32 planeAA, f32 planeAB, f32 planeAC, f32 planeADist, f32 planeBA, f32 planeBB, f32 planeBC, f32 planeBDist, Vec3f* linePointA, Vec3f* linePointB, Vec3f* closestPoint);
s32 func_80179798(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3, Vec3f* param_4, Vec3f* param_5, Vec3f* param_6);
// void func_80179A44(void);
void func_80179B34(float fParm1, f32 fParm2, f32 fParm5, f32 fParm6, f32 param_5, f32 param_6, f32 param_7, float* param_8, float* param_9);
s32 func_80179B94(f32 planeAA, f32 planeAB, f32 planeAC, f32 planeADist, f32 planeBA, f32 planeBB, f32 planeBC, f32 planeBDist, InfiniteLine* intersect);
// void func_80179D74(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10);
void Math3D_ScaleAndAdd(Vec3f* a, Vec3f* b, f32 scale, Vec3f* dst);
void Math3D_Lerp(Vec3f* a, Vec3f* b, f32 t, Vec3f* dst);
f32 Math3D_Parallel(Vec3f* a, Vec3f* b);
s32 Math3D_AngleBetweenVectors(Vec3f* a, Vec3f* b, f32* angle);
void func_80179F64(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3);
s32 Math3D_XZBoundCheck(f32 xMin, f32 xMax, f32 zMin, f32 zMax, f32 x, f32 z);
// void func_8017A09C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6);
// void func_8017A1D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6);
s32 func_8017A304(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 z, f32 x, f32 chkDist);
// UNK_TYPE4 func_8017A438(Vec3f* pfParm1, Vec3f* pfParm2, Vec3f* pfParm3, Vec3f* pfParm4, f32 param_5);
f32 Math3D_XZLengthSquared(f32 x, f32 z);
f32 Math3D_XZLength(f32 x, f32 z);
f32 Math3D_XZDistanceSquared(f32 x1, f32 x2, f32 z1, f32 z2);
f32 Math3D_XZDistance(f32 x1, f32 x2, f32 z1, f32 z2);
f32 Math3D_LengthSquared(Vec3f* vec);
f32 Math3D_Vec3fMagnitude(Vec3f* vec);
f32 Math3D_Vec3fDistSq(Vec3f* a, Vec3f* b);
f32 Math3D_Distance(Vec3f* a, Vec3f* b);
f32 Math3D_DistanceS(Vec3s* s, Vec3f* f);
f32 Math3D_Vec3fDiff_CrossZ(Vec3f* a, Vec3f* b, f32 dx, f32 dy);
f32 Math3D_Vec3fDiff_CrossX(Vec3f* a, Vec3f* b, f32 dy, f32 dz);
f32 Math3D_Vec3fDiff_CrossY(Vec3f* a, Vec3f* b, f32 dz, f32 dx);
void Math3D_CrossProduct(Vec3f* a, Vec3f* b, Vec3f* res);
void Math3D_SurfaceNorm(Vec3f* a, Vec3f* b, Vec3f* c, Vec3f* res);
s32 Math3D_PointRelativeToCubeFaces(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3);
s32 Math3D_PointRelativeToCubeEdges(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3);
s32 Math3D_PointRelativeToCubeVertices(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3);
s32 Math3D_LineVsCube(Vec3f* min, Vec3f* max, Vec3f* a, Vec3f* b);
s32 Math3D_LineVsCubeShort(Vec3s* min, Vec3s* max, Vec3s* a, Vec3s* b);
void func_8017B7F8(Vec3f* arg0, s16 arg1, f32* arg2, f32* arg3, f32* arg4);
void Math3D_UnitNormalVector(Vec3f* a, Vec3f* b, Vec3f* c, f32* normX, f32* normY, f32* normZ, f32* param_7);
f32 Math3D_SignedDistanceFromPlane(f32 normX, f32 normY, f32 normZ, f32 d, Vec3f* position);
f32 func_8017B9D8(Plane* plane, Vec3f* pointOnPlane);
f32 Math3D_UDistPlaneToPos(f32 normX, f32 normY, f32 normZ, f32 d, Vec3f* position);
f32 Math3D_DistPlaneToPos(f32 normX, f32 normY, f32 normZ, f32 d, Vec3f* position);
s32 Math3D_TriChkPointParaYDist(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 y, f32 z, f32 unk, f32 chkDist, f32 ny);
// void func_8017BD98(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
// void func_8017BDE0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
s32 Math3D_TriChkPointParaYIntersectDist(Vec3f* a, Vec3f* b, Vec3f* c, f32 nx, f32 ny, f32 nz, f32 dist, f32 z, f32 x, f32* yIntersect, f32 chkDist);
s32 Math3D_TriChkPointParaYIntersectInsideTri(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 z, f32 x, f32* yIntersect, f32 chkDist);
// void func_8017BF8C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6);
s32 Math3D_TriChkLineSegParaYIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 z, f32 x, f32* yIntersect, f32 y0, f32 y1);
// void func_8017C17C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
// void func_8017C1F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8);
s32 Math3D_TriChkPointParaYIntersectInsideTri2(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 z, f32 x, f32* yIntersect, f32 chkDist);
s32 Math3D_TriChkPointParaXDist(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 y, f32 z, f32 unk, f32 chkDist, f32 nx);
// void func_8017C808(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
s32 Math3D_TriChkPointParaXIntersect(Vec3f* a, Vec3f* b, Vec3f* c, f32 nx, f32 ny, f32 nz, f32 dist, f32 y, f32 z, f32* xIntersect);
// void func_8017C904(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6);
s32 Math3D_TriChkLineSegParaXIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 y, f32 z, f32* xIntersect, f32 x0, f32 x1);
// void func_8017CB08(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
s32 Math3D_TriChkLineSegParaZDist(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 y, f32 z, f32 unk, f32 chkDist, f32 nz);
// void func_8017CEA8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
s32 Math3D_TriChkPointParaZIntersect(Vec3f* a, Vec3f* b, Vec3f* c, f32 nx, f32 ny, f32 nz, f32 dist, f32 x, f32 y, f32* zIntersect);
// void func_8017CFA4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6);
s32 Math3D_TriChkLineSegParaZIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 x, f32 y, f32* zIntersect, f32 z0, f32 z1);
// void func_8017D1AC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
// void func_8017D220(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
s32 Math3D_LineSegVsPlane(f32 nx, f32 ny, f32 nz, f32 originDist, Vec3f* linePointA, Vec3f* linePointB, Vec3f* intersect, s32 fromFront);
s32 func_8017D404(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, Vec3f* linePointA, Vec3f* linePointB, Vec3f* intersect, s32 fromFront) ;
void Math3D_TriSetCoords(TriNorm* tri, Vec3f* pointA, Vec3f* pointB, Vec3f* pointC);
s32 Math3D_IsPointInSphere(Sphere16* sphere, Vec3f* point);
s32 Math3D_PointDistToLine2D(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32* arg6, f32* arg7, f32* arg8); // returns boolean
s32 func_8017D7C0(f32 x0, f32 y0, f32 x1, f32 y1, f32 x2, f32 y2, f32* lineLenSq);
s32 func_8017D814(f32 x0, f32 y0, Vec3f* p1, Vec3f* p2, f32* lineLenSq);
s32 func_8017D91C(f32 y0, f32 z0, Vec3f* p1, Vec3f* p2, f32* lineLenSq);
s32 func_8017DA24(f32 z0, f32 x0, Vec3f* p1, Vec3f* p2, f32* lineLenSq);
s32 Math3D_LineVsSph(Sphere16* sphere, Linef* line);
void func_8017DD34(Sphere16* sphere, TriNorm* tri, Vec3f* pfParm3);
s32 Math3D_ColSphereTri(Sphere16* sphere, TriNorm* tri, Vec3f* uParm3);
s32 func_8017E294(Cylinder16* cyl, Vec3f* point);
s32 func_8017E350(Cylinder16* cyl, Vec3f* linePointA, Vec3f* linePointB, Vec3f* intersectA, Vec3f* intersectB);
s32 Math3D_ColCylinderTri(Cylinder16* cylinder, TriNorm* tri, Vec3f* pzParm3);
// void func_8017F1A0(void);
s32 Math3D_SphVsSph(Sphere16* sphere1, Sphere16* sphere2);
s32 Math3D_ColSphereSphereIntersect(Sphere16* sphere1, Sphere16* sphere2, f32* intersectAmount);
s32 Math3D_ColSphereSphereIntersectAndDistance(Sphere16* sphere1, Sphere16* sphere2, f32* intersectAmount, f32* dist);
s32 Math3D_ColSphereCylinderDistance(Sphere16* sphere, Cylinder16* cylinder, f32* dist);
s32 Math3D_ColSphereCylinderDistanceAndAmount(Sphere16* sphere, Cylinder16* cylinder, f32* dist, f32* intersectAmount);
s32 Math3D_ColCylinderCylinderAmount(Cylinder16* cylinder1, Cylinder16* cylinder2, f32* intersectAmount);
s32 Math3D_ColCylinderCylinderAmountAndDistance(Cylinder16* cylinder1, Cylinder16* cylinder2, f32* intersectAmount, f32* dist);
s32 Math3d_ColTriTri(TriNorm* tri1, TriNorm* tri2, Vec3f* uParm3);
s32 Math3D_XZInSphere(Sphere16* sphere, f32 x, f32 z);
s32 Math3D_XYInSphere(Sphere16* sphere, f32 x, f32 y);
s32 Math3D_YZInSphere(Sphere16* sphere, f32 y, f32 z);
// void func_8017FB1C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11);
// void func_8017FD44(void);

#endif
