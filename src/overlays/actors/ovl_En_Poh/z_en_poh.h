#ifndef _Z_EN_POH_H_
#define _Z_EN_POH_H_

#include <global.h>

struct EnPoh;

typedef struct EnPoh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2D4];
} EnPoh; // size = 0x418

extern const ActorInit En_Poh_InitVars;

#endif
