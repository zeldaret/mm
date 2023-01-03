#ifndef Z_EN_HONOTRAP_H
#define Z_EN_HONOTRAP_H

#include "global.h"

struct EnHonotrap;

typedef void (*EnHonotrapActionFunc)(struct EnHonotrap*, PlayState*);

typedef union {
    struct {
        ColliderTris tris;
        ColliderTrisElement elements[2];
    };
    ColliderCylinder cyl;
} EnHonotrapCollider; // size = 0xD8

typedef struct {
    /* 0x00 */ Vec3f unk0;
    /* 0x0C */ f32  unkC;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ u8 unk12;
} EnHonotrapArr; //size 0x14

typedef struct {
    char unk0[0x8];
    f32 unk_08;
    EnHonotrapArr unkC[6];
} EnHonotrap23C;

typedef struct EnHonotrap {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnHonotrapActionFunc actionFunc;
    /* 0x148 */ EnHonotrapCollider collider;
    /* 0x220 */ s16 unk220;
    /* 0x222 */ s16 unk222;
    /* 0x224 */ s16 unk224;
    /* 0x228 */ Vec3f unk228;
    /* 0x234 */ char pad234[4];
    /* 0x238 */ s16 unk238;
    /* 0x23A */ s16 unk23A;
    /* 0x23C */ EnHonotrap23C unk23C;
    /* 0x2C0 */ s8 unk2C0;
} EnHonotrap; // size = 0x2C4

#endif // Z_EN_HONOTRAP_H
