#ifndef Z_DM_SA_H
#define Z_DM_SA_H

#include <global.h>

struct DmSa;

typedef struct DmSa {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1B0];
} DmSa; // size = 0x2F4

extern const ActorInit Dm_Sa_InitVars;

#endif // Z_DM_SA_H
