#ifndef Z_DM_CHAR04_H
#define Z_DM_CHAR04_H

#include "global.h"

struct DmChar04;

typedef void (*DmChar04ActionFunc)(struct DmChar04*, GlobalContext*);

typedef struct DmChar04 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xF8];
    /* 0x023C */ DmChar04ActionFunc actionFunc;
    /* 0x0240 */ char unk_240[0x24];
} DmChar04; // size = 0x264

extern const ActorInit Dm_Char04_InitVars;

#endif // Z_DM_CHAR04_H
