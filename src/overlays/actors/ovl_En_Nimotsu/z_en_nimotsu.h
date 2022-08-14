#ifndef Z_EN_NIMOTSU_H
#define Z_EN_NIMOTSU_H

#include "global.h"

struct EnNimotsu;

typedef struct EnNimotsu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char pad144[0x48];
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ u16 unk1D8;
    /* 0x1DA */ s16 framesUntilSomething;
} EnNimotsu; /* size = 0x1DC */

extern const ActorInit En_Nimotsu_InitVars;

#endif // Z_EN_NIMOTSU_H
