#ifndef Z_EN_LOOK_NUTS_H
#define Z_EN_LOOK_NUTS_H

#include "global.h"

struct EnLookNuts;

typedef void (*EnLookNutsActionFunc)(struct EnLookNuts*, GlobalContext*);

typedef struct EnLookNuts {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xC8];
    /* 0x020C */ EnLookNutsActionFunc actionFunc;
    /* 0x0210 */ char unk_210[0x80];
} EnLookNuts; // size = 0x290

extern const ActorInit En_Look_Nuts_InitVars;

#endif // Z_EN_LOOK_NUTS_H
