#ifndef _Z_EN_FLOORMAS_H_
#define _Z_EN_FLOORMAS_H_

#include <global.h>

struct EnFloormas;

typedef struct EnFloormas {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x25C];
} EnFloormas; // size = 0x3A0

extern const ActorInit En_Floormas_InitVars;

#endif
