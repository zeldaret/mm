#ifndef Z_BG_KIN2_PICTURE_H
#define Z_BG_KIN2_PICTURE_H

#include "global.h"

struct BgKin2Picture;

typedef void (*BgKin2PictureActionFunc)(struct BgKin2Picture*, PlayState*);

typedef struct BgKin2Picture {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xF0];
    /* 0x234 */ BgKin2PictureActionFunc actionFunc;
    /* 0x238 */ char unk_238[0xC];
} BgKin2Picture; // size = 0x244

extern const ActorInit Bg_Kin2_Picture_InitVars;

#endif // Z_BG_KIN2_PICTURE_H
