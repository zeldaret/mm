#ifndef Z_EN_FU_H
#define Z_EN_FU_H

#include <global.h>

struct EnFu;

typedef struct EnFu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x410];
} EnFu; // size = 0x554

extern const ActorInit En_Fu_InitVars;

#endif // Z_EN_FU_H
