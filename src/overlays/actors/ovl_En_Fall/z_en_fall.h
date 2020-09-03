#ifndef Z_EN_FALL_H
#define Z_EN_FALL_H

#include <global.h>

struct EnFall;

typedef struct EnFall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x20];
} EnFall; // size = 0x164

extern const ActorInit En_Fall_InitVars;

#endif // Z_EN_FALL_H
