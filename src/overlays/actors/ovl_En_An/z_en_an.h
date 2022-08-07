#ifndef Z_EN_AN_H
#define Z_EN_AN_H

#include "global.h"

struct EnAn;

typedef void (*EnAnActionFunc)(struct EnAn*, PlayState*);

typedef struct EnAn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x44];
    /* 0x188 */ EnAnActionFunc actionFunc;
    /* 0x18C */ char unk_18C[0x23C];
} EnAn; // size = 0x3C8

extern const ActorInit En_An_InitVars;

#endif // Z_EN_AN_H
