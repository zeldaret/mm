#ifndef Z_EN_AL_H
#define Z_EN_AL_H

#include <global.h>

struct EnAl;

typedef struct EnAl {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x3BC];
} EnAl; // size = 0x500

extern const ActorInit En_Al_InitVars;

#endif // Z_EN_AL_H
