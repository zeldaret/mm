#ifndef _Z_EN_BAT_H_
#define _Z_EN_BAT_H_

#include <global.h>

struct EnBat;

typedef struct EnBat {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x98];
} EnBat; // size = 0x1DC

extern const ActorInit En_Bat_InitVars;

#endif
