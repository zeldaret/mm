#ifndef Z_EN_PRZ_H
#define Z_EN_PRZ_H

#include <global.h>

struct EnPrz;

typedef struct EnPrz {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x12C];
} EnPrz; // size = 0x270

extern const ActorInit En_Prz_InitVars;

#endif // Z_EN_PRZ_H
