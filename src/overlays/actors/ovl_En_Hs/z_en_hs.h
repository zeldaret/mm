#ifndef Z_EN_HS_H
#define Z_EN_HS_H

#include "global.h"

struct EnHs;

typedef void (*EnHsActionFunc)(struct EnHs*, GlobalContext*);

typedef struct EnHs {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x160];
    /* 0x2A4 */ Vec3f nwcPos[20]; // positions of chicks during breman march
    /* 0x394 */ EnHsActionFunc actionFunc;
} EnHs; // size = 0x398

extern const ActorInit En_Hs_InitVars;

#endif // Z_EN_HS_H
