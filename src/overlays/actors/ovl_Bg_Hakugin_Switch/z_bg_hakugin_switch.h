#ifndef _Z_BG_HAKUGIN_SWITCH_H_
#define _Z_BG_HAKUGIN_SWITCH_H_

#include <global.h>

struct BgHakuginSwitch;

typedef struct BgHakuginSwitch {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x88];
} BgHakuginSwitch; // size = 0x1CC

extern const ActorInit Bg_Hakugin_Switch_InitVars;

#endif
