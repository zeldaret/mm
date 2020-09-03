#ifndef Z_EN_HORSE_H
#define Z_EN_HORSE_H

#include <global.h>

struct EnHorse;

typedef struct EnHorse {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x450];
} EnHorse; // size = 0x594

extern const ActorInit En_Horse_InitVars;

#endif // Z_EN_HORSE_H
