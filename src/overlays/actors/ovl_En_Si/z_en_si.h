#ifndef Z_EN_SI_H
#define Z_EN_SI_H

#include <global.h>

struct EnSi;

typedef struct EnSi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x5C];
} EnSi; // size = 0x1A0

extern const ActorInit En_Si_InitVars;

#endif // Z_EN_SI_H
