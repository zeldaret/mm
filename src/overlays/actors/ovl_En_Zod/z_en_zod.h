#ifndef Z_EN_ZOD_H
#define Z_EN_ZOD_H

#include "global.h"
#include "assets/objects/object_zod/object_zod.h"

#define ENZOD_GET_ENTRANCE_INDEX(thisx) (((thisx)->params & 0xFE00) >> 9)

struct EnZod;

typedef void (*EnZodActionFunc)(struct EnZod*, PlayState*);

typedef struct EnZod {
    /* 0x000 */ Actor actor;
    /* 0x144 */ Vec3s morphTable[OBJECT_ZOD_LIMB_MAX];
    /* 0x180 */ Vec3s JointTable[OBJECT_ZOD_LIMB_MAX];
    /* 0x1BC */ SkelAnime skelAnime;
    /* 0x200 */ ColliderCylinder collider;
    /* 0x24C */ s16 unk24C;
    /* 0x24E */ s16 unk24E;
    /* 0x250 */ Vec3s headRot;
    /* 0x256 */ u16 unk256;
    /* 0x258 */ s16 unk258;
    /* 0x25A */ s16 unk25A;
    /* 0x25C */ s16 unk25C[3];
    /* 0x262 */ s16 unk262[3];
    /* 0x268 */ f32 unk268[6];
    /* 0x280 */ f32 unk280[6];
    /* 0x298 */ s16 unk298;
    /* 0x29A */ s16 fogNear;
    /* 0x29C */ EnZodActionFunc actionFunc;
} EnZod; // size = 0x2A0

extern const ActorInit En_Zod_InitVars;

#endif // Z_EN_ZOD_H
