#ifndef Z_EN_AZ_H
#define Z_EN_AZ_H

#include "global.h"

struct EnAz;

typedef void (*EnAzActionFunc)(struct EnAz*, PlayState*);

typedef struct EnAz {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnAzActionFunc actionFunc;
    /* 0x148 */ char unk_148[0x290];
} EnAz; // size = 0x3D8

extern const ActorInit En_Az_InitVars;

#endif // Z_EN_AZ_H
