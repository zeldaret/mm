#ifndef Z_EN_FISHING_H
#define Z_EN_FISHING_H

#include "global.h"

struct EnFishing;

typedef void (*EnFishingActionFunc)(struct EnFishing*, GlobalContext*);

typedef struct EnFishing {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x404];
} EnFishing; // size = 0x548

extern const ActorInit En_Fishing_InitVars;

#endif // Z_EN_FISHING_H
