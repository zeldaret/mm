#ifndef Z_EN_YB_H
#define Z_EN_YB_H

#include <global.h>

struct EnYb;

typedef struct EnYb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2E0];
} EnYb; // size = 0x424

extern const ActorInit En_Yb_InitVars;

#endif // Z_EN_YB_H
