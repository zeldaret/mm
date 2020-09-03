#ifndef _Z_MIR_RAY3_H_
#define _Z_MIR_RAY3_H_

#include <global.h>

struct MirRay3;

typedef struct MirRay3 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x120];
} MirRay3; // size = 0x264

extern const ActorInit Mir_Ray3_InitVars;

#endif
