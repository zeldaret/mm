#ifndef _Z_DM_CHAR04_H_
#define _Z_DM_CHAR04_H_

#include <global.h>

struct DmChar04;

typedef struct DmChar04 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x120];
} DmChar04; // size = 0x264

extern const ActorInit Dm_Char04_InitVars;

#endif
