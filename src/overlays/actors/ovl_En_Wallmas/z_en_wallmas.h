#ifndef _Z_EN_WALLMAS_H_
#define _Z_EN_WALLMAS_H_

#include <global.h>

struct EnWallmas;

typedef struct EnWallmas {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x260];
} EnWallmas; // size = 0x3A4

extern const ActorInit En_Wallmas_InitVars;

#endif
