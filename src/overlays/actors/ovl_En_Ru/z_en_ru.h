#ifndef _Z_EN_RU_H_
#define _Z_EN_RU_H_

#include <global.h>

struct EnRu;

typedef struct EnRu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x310];
} EnRu; // size = 0x454

extern const ActorInit En_Ru_InitVars;

#endif
