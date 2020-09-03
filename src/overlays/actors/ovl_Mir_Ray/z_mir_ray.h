#ifndef _Z_MIR_RAY_H_
#define _Z_MIR_RAY_H_

#include <global.h>

struct MirRay;

typedef struct MirRay {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x164];
} MirRay; // size = 0x2A8

extern const ActorInit Mir_Ray_InitVars;

#endif
