#ifndef Z_EN_GEG_H
#define Z_EN_GEG_H

#include "global.h"

struct EnGeg;

typedef void (*EnGegActionFunc)(struct EnGeg*, GlobalContext*);

typedef struct EnGeg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnGegActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x364];
} EnGeg; // size = 0x4F0

extern const ActorInit En_Geg_InitVars;

#endif // Z_EN_GEG_H
