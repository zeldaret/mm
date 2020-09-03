#ifndef Z_EN_GK_H
#define Z_EN_GK_H

#include <global.h>

struct EnGk;

typedef struct EnGk {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x214];
} EnGk; // size = 0x358

extern const ActorInit En_Gk_InitVars;

#endif // Z_EN_GK_H
