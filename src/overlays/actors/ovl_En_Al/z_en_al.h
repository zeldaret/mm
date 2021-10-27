#ifndef Z_EN_AL_H
#define Z_EN_AL_H

#include "global.h"

struct EnAl;

typedef void (*EnAlActionFunc)(struct EnAl*, GlobalContext*);

typedef struct EnAl {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnAlActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x374];
} EnAl; // size = 0x500

extern const ActorInit En_Al_InitVars;

#endif // Z_EN_AL_H
