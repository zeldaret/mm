#ifndef Z_EN_ZOG_H
#define Z_EN_ZOG_H

#include "global.h"

struct EnZog;

typedef void (*EnZogActionFunc)(struct EnZog*, GlobalContext*);

typedef struct EnZog {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1E4];
    /* 0x0328 */ EnZogActionFunc actionFunc;
} EnZog; // size = 0x32C

extern const ActorInit En_Zog_InitVars;

#endif // Z_EN_ZOG_H
