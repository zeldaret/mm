#ifndef Z_EN_NIMOTSU_H
#define Z_EN_NIMOTSU_H

#include <global.h>

struct EnNimotsu;

typedef struct EnNimotsu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x98];
} EnNimotsu; // size = 0x1DC

extern const ActorInit En_Nimotsu_InitVars;

#endif // Z_EN_NIMOTSU_H
