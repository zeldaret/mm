#ifndef Z_EN_SHN_H
#define Z_EN_SHN_H

#include <global.h>

struct EnShn;

typedef struct EnShn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1AC];
} EnShn; // size = 0x2F0

extern const ActorInit En_Shn_InitVars;

#endif // Z_EN_SHN_H
