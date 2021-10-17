#ifndef Z_DM_CHAR01_H
#define Z_DM_CHAR01_H

#include "global.h"

struct DmChar01;

typedef void (*DmChar01ActionFunc)(struct DmChar01*, GlobalContext*);

typedef struct DmChar01 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x5C];
    /* 0x01A0 */ DmChar01ActionFunc actionFunc;
    /* 0x01A4 */ char unk_1A4[0x1AC];
} DmChar01; // size = 0x350

extern const ActorInit Dm_Char01_InitVars;

#endif // Z_DM_CHAR01_H
