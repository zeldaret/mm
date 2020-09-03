#ifndef _Z_DM_STATUE_H_
#define _Z_DM_STATUE_H_

#include <global.h>

struct DmStatue;

typedef struct DmStatue {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x50];
} DmStatue; // size = 0x194

extern const ActorInit Dm_Statue_InitVars;

#endif
