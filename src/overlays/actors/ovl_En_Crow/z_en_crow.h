#ifndef _Z_EN_CROW_H_
#define _Z_EN_CROW_H_

#include <global.h>

struct EnCrow;

typedef struct EnCrow {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x158];
} EnCrow; // size = 0x29C

extern const ActorInit En_Crow_InitVars;

#endif
