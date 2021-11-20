#ifndef Z_DM_AL_H
#define Z_DM_AL_H

#include "global.h"

struct DmAl;

typedef void (*DmAlActionFunc)(struct DmAl*, GlobalContext*);

typedef struct DmAl {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ DmAlActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x2D4];
} DmAl; // size = 0x460

extern const ActorInit Dm_Al_InitVars;

#endif // Z_DM_AL_H
