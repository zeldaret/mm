#ifndef Z_BG_CTOWER_ROT_H
#define Z_BG_CTOWER_ROT_H

#include <global.h>

struct BgCtowerRot;

typedef struct BgCtowerRot {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x24];
} BgCtowerRot; // size = 0x168

extern const ActorInit Bg_Ctower_Rot_InitVars;

#endif // Z_BG_CTOWER_ROT_H
