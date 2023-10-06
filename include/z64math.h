#ifndef Z64MATH_H
#define Z64MATH_H

#include "ultra64.h"

#define VEC_SET(V,X,Y,Z) V.x=X;V.y=Y;V.z=Z

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 z;
} Vec2s; // size = 0x4

typedef struct {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 z;
} Vec2f; // size = 0x8

typedef struct {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} Vec3f; // size = 0xC

typedef struct {
    /* 0x0 */ u16 x;
    /* 0x2 */ u16 y;
    /* 0x4 */ u16 z;
} Vec3us; // size = 0x6

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} Vec3s; // size = 0x6

typedef struct {
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
    /* 0x8 */ s32 z;
} Vec3i; // size = 0xC

typedef struct {
    /* 0x0 */ f32 distance;
    /* 0x4 */ s16 angle;
} VecPolar; // size = 0x8

typedef struct {
    /* 0x0 */ Vec3s center;
    /* 0x6 */ s16   radius;
} Sphere16; // size = 0x8

typedef struct {
    /* 0x0 */ Vec3f center;
    /* 0xC */ f32   radius;
} Spheref; // size = 0x10

/*
The plane paramaters are of form `ax + by + cz + d = 0`
where `(a,b,c)` is the plane's normal vector and d is the originDist
 */
typedef struct {
    /* 0x00 */ Vec3f normal;
    /* 0x0C */ f32   originDist;
} Plane; // size = 0x10

typedef struct {
    /* 0x00 */ Vec3f vtx[3];
    /* 0x24 */ Plane plane;
} TriNorm; // size = 0x34

typedef struct {
    /* 0x0 */ s16   radius;
    /* 0x2 */ s16   height;
    /* 0x4 */ s16   yShift;
    /* 0x6 */ Vec3s pos;
} Cylinder16; // size = 0xC

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
} LineSegment; // size = 0x18

typedef struct {
    /* 0x0 */ f32 r; // radius
    /* 0x4 */ s16 pitch; // depends on coordinate system. See below.
    /* 0x6 */ s16 yaw; // azimuthal angle
} VecSphGeo; // size = 0x8

// Defines a point in the spherical coordinate system.
// Pitch is 0 along the positive y-axis (up)
typedef VecSphGeo VecSph;

// Defines a point in the geographic coordinate system.
// Pitch is 0 along the xz-plane (horizon)
typedef VecSphGeo VecGeo;

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

typedef float MtxF_t[4][4];
typedef union {
    MtxF_t mf;
    struct {
        float xx, yx, zx, wx,
              xy, yy, zy, wy,
              xz, yz, zz, wz,
              xw, yw, zw, ww;
    };
} MtxF; // size = 0x40

#define LERPIMP(v0, v1, t) ((v0) + (((v1) - (v0)) * (t)))
#define F32_LERP(v0, v1, t) ((1.0f - (t)) * (f32)(v0) + (t) * (f32)(v1))
#define F32_LERPIMP(v0, v1, t) ((f32)(v0) + (((f32)(v1) - (f32)(v0)) * (t)))
#define F32_LERPIMPINV(v0, v1, t) ((f32)(v0) + (((f32)(v1) - (f32)(v0)) / (t)))
#define BINANG_LERPIMP(v0, v1, t) ((v0) + (s16)(BINANG_SUB((v1), (v0)) * (t)))
#define BINANG_LERPIMPINV(v0, v1, t) ((v0) + BINANG_SUB((v1), (v0)) / (t))

#define LERPWEIGHT(val, prev, next) (((val) - (prev)) / ((next) - (prev)))
#define F32_LERPWEIGHT(val, prev, next) (((f32)(val) - (f32)(prev)) / ((f32)(next) - (f32)(prev)))

#define VEC3F_LERPIMPDST(dst, v0, v1, t)                \
    {                                                   \
        (dst)->x = (v0)->x + (((v1)->x - (v0)->x) * t); \
        (dst)->y = (v0)->y + (((v1)->y - (v0)->y) * t); \
        (dst)->z = (v0)->z + (((v1)->z - (v0)->z) * t); \
    }                                                   \
    (void)0

#define IS_ZERO(f) (fabsf(f) < 0.008f)

// Casting a float to an integer, when the float value is larger than what the integer type can hold,
// leads to undefined behavior. For example (f32)0x8000 doesn't fit in a s16, so it cannot be cast to s16.
// This isn't an issue with IDO, but is one with for example GCC.
// A partial workaround is to cast to s32 then s16, hoping all binang values used will fit a s32.
#define TRUNCF_BINANG(f) (s16)(s32)(f)

// Angle conversion macros
#define DEG_TO_RAD(degrees) ((degrees) * (M_PI / 180.0f))
#define DEG_TO_BINANG(degrees) TRUNCF_BINANG((degrees) * (0x8000 / 180.0f))
#define DEG_TO_BINANG_ALT(degrees) TRUNCF_BINANG(((degrees) / 180.0f) * 0x8000)
#define DEG_TO_BINANG_ALT2(degrees) TRUNCF_BINANG(((degrees) * 0x10000) / 360.0f)
#define DEG_TO_BINANG_ALT3(degrees) ((degrees) * (0x8000 / 180.0f))

#define RAD_TO_DEG(radians) ((radians) * (180.0f / M_PI))
#define RAD_TO_BINANG(radians) TRUNCF_BINANG((radians) * (0x8000 / M_PI))
#define RAD_TO_BINANG_ALT(radians) TRUNCF_BINANG(((radians) / M_PI) * 0x8000)
#define RAD_TO_BINANG_ALT2(radians) TRUNCF_BINANG(((radians) * 0x8000) / M_PI)

#define BINANG_TO_DEG(binang) ((f32)(binang) * (180.0f / 0x8000))
#define BINANG_TO_RAD(binang) ((f32)(binang) * (M_PI / 0x8000))
#define BINANG_TO_RAD_ALT(binang) (((f32)(binang) / 0x8000) * M_PI)
#define BINANG_TO_RAD_ALT2(binang) (((f32)(binang) * M_PI) / 0x8000)

// Angle arithmetic macros
#define BINANG_ROT180(angle) ((s16)(angle + 0x8000))
#define BINANG_SUB(a, b) ((s16)(a - b))
#define BINANG_ADD(a, b) ((s16)(a + b))

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
s16 Rand_S16Offset(s16 base, s16 range);
s16 Rand_S16OffsetStride(s16 base, s16 stride, s16 range);
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

f32 Math_FactorialF(f32 n);
f32 Math_Factorial(s32 n);
f32 Math_PowF(f32 base, s32 exp);
f32 Math_SinF(f32 rad);
f32 Math_CosF(f32 rad);
f32 Rand_ZeroFloat(f32 scale);
f32 Rand_CenteredFloat(f32 scale);

f32 Math_FTanF(f32 x);
f32 Math_FFloorF(f32 x);
f32 Math_FCeilF(f32 x);
f32 Math_FRoundF(f32 x);
f32 Math_FTruncF(f32 x);
f32 Math_FNearbyIntF(f32 x);
f32 Math_FAtanTaylorQF(f32 x);
f32 Math_FAtanTaylorF(f32 x);
f32 Math_FAtanContFracF(f32 x);
f32 Math_FAtanF(f32 x);
f32 Math_FAtan2F(f32 y, f32 x);
f32 Math_FAsinF(f32 x);
f32 Math_FAcosF(f32 x);

s16 Math_Atan2S(f32 y, f32 x);
f32 Math_Atan2F(f32 y, f32 x);
s16 Math_Atan2S_XY(f32 x, f32 y);
f32 Math_Atan2F_XY(f32 x, f32 y);

#endif
