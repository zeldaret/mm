#ifndef Z_EN_RZ_H
#define Z_EN_RZ_H

#include <global.h>

struct EnRz;

typedef struct EnRz {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2F0];
} EnRz; // size = 0x434

extern const ActorInit En_Rz_InitVars;

#endif // Z_EN_RZ_H
