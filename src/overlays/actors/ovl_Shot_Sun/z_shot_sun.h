#ifndef Z_SHOT_SUN_H
#define Z_SHOT_SUN_H

#include "global.h"

struct ShotSun;

typedef void (*ShotSunActionFunc)(struct ShotSun*, PlayState*);

typedef struct ShotSun {
    /* 0x0000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ ShotSunActionFunc actionFunc;
    /* 0x194 */ Vec3s hitboxPos;                        /* inferred */
    /* 0x19A */ s16 unk19A;
    /* 0x19C */ s8 unk19C;
    /* 0x19D */ char pad19D[3];
} ShotSun; // size = 0x1A0

extern const ActorInit Shot_Sun_InitVars;

#endif // Z_SHOT_SUN_H
