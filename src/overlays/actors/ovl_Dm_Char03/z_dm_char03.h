#ifndef Z_DM_CHAR03_H
#define Z_DM_CHAR03_H

#include "global.h"

struct DmChar03;

typedef void (*DmChar03ActionFunc)(struct DmChar03*, GlobalContext*);

typedef struct DmChar03 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ DmChar03ActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x10];
} DmChar03; // size = 0x19C

extern const ActorInit Dm_Char03_InitVars;

#endif // Z_DM_CHAR03_H
