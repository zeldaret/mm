#ifndef Z_EN_BOX_H
#define Z_EN_BOX_H

#include "global.h"

struct EnBox;

typedef void (*EnBoxActionFunc)(struct EnBox*, GlobalContext*);

typedef struct EnBox {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xBC];
    /* 0x0200 */ EnBoxActionFunc actionFunc;
    /* 0x0204 */ char unk_204[0x20];
} EnBox; // size = 0x224

extern const ActorInit En_Box_InitVars;

#endif // Z_EN_BOX_H
