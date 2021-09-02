#ifndef Z_DM_CHAR00_H
#define Z_DM_CHAR00_H

#include "global.h"

struct DmChar00;

typedef void (*DmChar00ActionFunc)(struct DmChar00*, GlobalContext*);

typedef struct DmChar00 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xF8];
    /* 0x023C */ DmChar00ActionFunc actionFunc;
    /* 0x0240 */ char unk_240[0x24];
} DmChar00; // size = 0x264

extern const ActorInit Dm_Char00_InitVars;

#endif // Z_DM_CHAR00_H
