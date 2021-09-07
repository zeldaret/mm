#ifndef Z_EN_FZ_H
#define Z_EN_FZ_H

#include "global.h"

struct EnFz;

typedef struct EnFz {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xA98];
} EnFz; // size = 0xBDC

extern const ActorInit En_Fz_InitVars;

#endif // Z_EN_FZ_H
