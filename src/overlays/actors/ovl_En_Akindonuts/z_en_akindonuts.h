#ifndef Z_EN_AKINDONUTS_H
#define Z_EN_AKINDONUTS_H

#include "global.h"

struct EnAkindonuts;

typedef void (*EnAkindonutsActionFunc)(struct EnAkindonuts*, GlobalContext*);

typedef struct EnAkindonuts {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x194];
    /* 0x02D8 */ EnAkindonutsActionFunc actionFunc;
    /* 0x02DC */ char unk_2DC[0x90];
} EnAkindonuts; // size = 0x36C

extern const ActorInit En_Akindonuts_InitVars;

#endif // Z_EN_AKINDONUTS_H
