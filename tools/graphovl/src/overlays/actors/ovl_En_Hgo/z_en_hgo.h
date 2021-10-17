#ifndef Z_EN_HGO_H
#define Z_EN_HGO_H

#include "global.h"

struct EnHgo;

typedef void (*EnHgoActionFunc)(struct EnHgo*, GlobalContext*);

typedef struct EnHgo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x90];
    /* 0x01D4 */ EnHgoActionFunc actionFunc;
    /* 0x01D8 */ char unk_1D8[0x140];
} EnHgo; // size = 0x318

extern const ActorInit En_Hgo_InitVars;

#endif // Z_EN_HGO_H
