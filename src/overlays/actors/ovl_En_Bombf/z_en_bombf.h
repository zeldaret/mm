#ifndef Z_EN_BOMBF_H
#define Z_EN_BOMBF_H

#include "global.h"

struct EnBombf;

typedef void (*EnBombfActionFunc)(struct EnBombf*, GlobalContext*);

typedef struct EnBombf {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xAC];
    /* 0x1F0 */ s16 timer;
    /* 0x1F2 */ char unk_1F2[0x16];
} EnBombf; // size = 0x208

extern const ActorInit En_Bombf_InitVars;

#endif // Z_EN_BOMBF_H
