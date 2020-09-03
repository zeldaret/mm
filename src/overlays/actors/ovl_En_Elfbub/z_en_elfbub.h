#ifndef Z_EN_ELFBUB_H
#define Z_EN_ELFBUB_H

#include <global.h>

struct EnElfbub;

typedef struct EnElfbub {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x60];
} EnElfbub; // size = 0x1A4

extern const ActorInit En_Elfbub_InitVars;

#endif // Z_EN_ELFBUB_H
