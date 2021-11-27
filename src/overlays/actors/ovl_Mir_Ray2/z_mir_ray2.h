#ifndef Z_MIR_RAY2_H
#define Z_MIR_RAY2_H

#include "global.h"

struct MirRay2;

typedef struct MirRay2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x7C];
} MirRay2; // size = 0x1C0

extern const ActorInit Mir_Ray2_InitVars;

#endif // Z_MIR_RAY2_H
