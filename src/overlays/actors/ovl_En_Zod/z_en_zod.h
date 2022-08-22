#ifndef Z_EN_ZOD_H
#define Z_EN_ZOD_H

#include "global.h"

struct EnZod;

typedef void (*EnZodActionFunc)(struct EnZod*, PlayState*);

typedef struct EnZod {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x158];
    /* 0x29C */ EnZodActionFunc actionFunc;
} EnZod; // size = 0x2A0

extern const ActorInit En_Zod_InitVars;

#endif // Z_EN_ZOD_H
