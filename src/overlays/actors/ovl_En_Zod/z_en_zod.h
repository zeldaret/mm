#ifndef Z_EN_ZOD_H
#define Z_EN_ZOD_H

#include "global.h"
//#include "assets/objects/object_zod/object_zod.h"

#define ENZOD_GET_ENTRANCE_INDEX(thisx) (((thisx)->params & 0xFE00) >> 9)

struct EnZod;

typedef void (*EnZodActionFunc)(struct EnZod*, PlayState*);

typedef struct EnZod {
    Actor actor;
    Vec3s morphTable;
    char pad14A[0x36];
    Vec3s JointTable;
    char pad186[0x36];
    SkelAnime skelAnime;
    ColliderCylinder collider;
    s16 unk24C;
    s16 unk24E;
    Vec3s headRot;
    u16 unk256;
    s16 unk258;
    s16 unk25A;
    s16 unk25C;
    s16 unk25E;
    s16 unk260;
    s16 unk262;
    s16 unk264;
    s16 unk266;
    f32 unk268[6];
    f32 unk280[6];
    s16 unk298;
    s16 unk29A;
    EnZodActionFunc actionFunc;
} EnZod; // size = 0x2A0

extern const ActorInit En_Zod_InitVars;

#endif // Z_EN_ZOD_H
