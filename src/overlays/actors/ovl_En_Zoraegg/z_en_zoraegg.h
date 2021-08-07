#ifndef Z_EN_ZORAEGG_H
#define Z_EN_ZORAEGG_H

#include "global.h"

struct EnZoraegg;

typedef void (*EnZoraeggActionFunc)(struct EnZoraegg* this, GlobalContext* globalCtx);

typedef struct EnZoraegg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xB4];
    /* 0x01F8 */ EnZoraeggActionFunc actionFunc;
} EnZoraegg; // size = 0x1FC

extern const ActorInit En_Zoraegg_InitVars;

#endif // Z_EN_ZORAEGG_H
