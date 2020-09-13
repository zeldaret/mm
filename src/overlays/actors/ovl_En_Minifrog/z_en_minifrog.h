#ifndef Z_EN_MINIFROG_H
#define Z_EN_MINIFROG_H

#include <global.h>

struct EnMinifrog;

typedef struct EnMinifrog {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1C0];
} EnMinifrog; // size = 0x304

extern const ActorInit En_Minifrog_InitVars;

#endif // Z_EN_MINIFROG_H
