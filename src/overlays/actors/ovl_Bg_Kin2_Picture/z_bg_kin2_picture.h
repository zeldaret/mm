#ifndef Z_BG_KIN2_PICTURE_H
#define Z_BG_KIN2_PICTURE_H

#include <global.h>

struct BgKin2Picture;

typedef struct BgKin2Picture {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x100];
} BgKin2Picture; // size = 0x244

extern const ActorInit Bg_Kin2_Picture_InitVars;

#endif // Z_BG_KIN2_PICTURE_H
