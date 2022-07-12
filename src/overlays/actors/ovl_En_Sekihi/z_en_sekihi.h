#ifndef Z_EN_SEKIHI_H
#define Z_EN_SEKIHI_H

#include "global.h"

struct EnSekihi;

typedef void (*EnSekihiActionFunc)(struct EnSekihi*, PlayState*);

typedef struct EnSekihi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x24];
    /* 0x168 */ EnSekihiActionFunc actionFunc;
} EnSekihi; // size = 0x16C

extern const ActorInit En_Sekihi_InitVars;

#endif // Z_EN_SEKIHI_H
