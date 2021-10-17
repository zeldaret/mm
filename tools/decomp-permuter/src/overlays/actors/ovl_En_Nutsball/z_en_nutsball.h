#ifndef Z_EN_NUTSBALL_H
#define Z_EN_NUTSBALL_H

#include <global.h>

struct EnNutsball;

typedef struct EnNutsball {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x50];
} EnNutsball; // size = 0x194

extern const ActorInit En_Nutsball_InitVars;

#endif // Z_EN_NUTSBALL_H
