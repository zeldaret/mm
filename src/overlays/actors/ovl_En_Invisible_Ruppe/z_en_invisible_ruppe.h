#ifndef Z_EN_INVISIBLE_RUPPE_H
#define Z_EN_INVISIBLE_RUPPE_H

#include "global.h"

struct EnInvisibleRuppe;

typedef void (*EnInvisibleRuppeActionFunc)(struct EnInvisibleRuppe*, GlobalContext*);

typedef struct EnInvisibleRuppe {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x50];
    /* 0x0194 */ EnInvisibleRuppeActionFunc actionFunc;
} EnInvisibleRuppe; // size = 0x198

extern const ActorInit En_Invisible_Ruppe_InitVars;

#endif // Z_EN_INVISIBLE_RUPPE_H
