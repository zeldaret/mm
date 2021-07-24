#ifndef Z_BG_HAKUGIN_SWITCH_H
#define Z_BG_HAKUGIN_SWITCH_H

#include "global.h"

struct BgHakuginSwitch;

typedef struct BgHakuginSwitch {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x88];
} BgHakuginSwitch; // size = 0x1CC

extern const ActorInit Bg_Hakugin_Switch_InitVars;

#endif // Z_BG_HAKUGIN_SWITCH_H
