#ifndef Z_EN_M_THUNDER_H
#define Z_EN_M_THUNDER_H

#include "global.h"

struct EnMThunder;

typedef void (*EnMThunderActionFunc)(struct EnMThunder*, PlayState*);

typedef struct EnMThunder {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x74];
    /* 0x1B8 */ EnMThunderActionFunc actionFunc;
    /* 0x1BC */ char unk_1BC[0x8];
} EnMThunder; // size = 0x1C4

extern const ActorInit En_M_Thunder_InitVars;

#endif // Z_EN_M_THUNDER_H
