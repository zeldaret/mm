#ifndef Z_EN_BOMBF_H
#define Z_EN_BOMBF_H

#include <global.h>

struct EnBombf;

typedef struct EnBombf {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xC4];
} EnBombf; // size = 0x208

extern const ActorInit En_Bombf_InitVars;

#endif // Z_EN_BOMBF_H
