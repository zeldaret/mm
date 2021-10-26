#ifndef Z_EN_FALL_H
#define Z_EN_FALL_H

#include "global.h"

struct EnFall;

typedef void (*EnFallActionFunc)(struct EnFall*, GlobalContext*);

typedef struct EnFall {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1C];
    /* 0x0160 */ EnFallActionFunc actionFunc;
} EnFall; // size = 0x164

extern const ActorInit En_Fall_InitVars;

#endif // Z_EN_FALL_H
