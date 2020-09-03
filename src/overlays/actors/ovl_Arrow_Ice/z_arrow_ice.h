#ifndef Z_ARROW_ICE_H
#define Z_ARROW_ICE_H

#include <global.h>

struct ArrowIce;

typedef struct ArrowIce {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x20];
} ArrowIce; // size = 0x164

extern const ActorInit Arrow_Ice_InitVars;

#endif // Z_ARROW_ICE_H
