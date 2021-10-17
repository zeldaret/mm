#ifndef Z_DM_TSG_H
#define Z_DM_TSG_H

#include <global.h>

struct DmTsg;

typedef struct DmTsg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x7DC];
} DmTsg; // size = 0x920

extern const ActorInit Dm_Tsg_InitVars;

#endif // Z_DM_TSG_H
