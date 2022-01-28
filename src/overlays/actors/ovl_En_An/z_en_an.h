#ifndef Z_EN_AN_H
#define Z_EN_AN_H

#include "global.h"

struct EnAn;

typedef void (*EnAnActionFunc)(struct EnAn*, GlobalContext*);

typedef struct EnAn {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnAnActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x23C];
} EnAn; // size = 0x3C8

extern const ActorInit En_An_InitVars;

#endif // Z_EN_AN_H
