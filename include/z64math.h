#ifndef _Z64MATH_H_
#define _Z64MATH_H_

#include "ultra64.h"

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
} LineSegment; // size = 0x18

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

#endif
