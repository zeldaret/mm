#ifndef Z_EN_PAMETFROG_H
#define Z_EN_PAMETFROG_H

#include <global.h>

struct EnPametfrog;

typedef struct EnPametfrog {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2E0];
} EnPametfrog; // size = 0x424

extern const ActorInit En_Pametfrog_InitVars;

#endif // Z_EN_PAMETFROG_H
