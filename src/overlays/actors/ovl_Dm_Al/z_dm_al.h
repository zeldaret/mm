#ifndef Z_DM_AL_H
#define Z_DM_AL_H

#include "global.h"

struct DmAl;

typedef struct DmAl {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x31C];
} DmAl; // size = 0x460

extern const ActorInit Dm_Al_InitVars;

#endif // Z_DM_AL_H
