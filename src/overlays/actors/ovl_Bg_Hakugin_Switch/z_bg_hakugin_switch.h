#ifndef Z_BG_HAKUGIN_SWITCH_H
#define Z_BG_HAKUGIN_SWITCH_H

#include "global.h"

struct BgHakuginSwitch;

typedef void (*BgHakuginSwitchActionFunc)(struct BgHakuginSwitch*, GlobalContext*);

typedef struct BgHakuginSwitch {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x68];
    /* 0x01AC */ BgHakuginSwitchActionFunc actionFunc;
    /* 0x01B0 */ char unk_1B0[0x1C];
} BgHakuginSwitch; // size = 0x1CC

extern const ActorInit Bg_Hakugin_Switch_InitVars;

#endif // Z_BG_HAKUGIN_SWITCH_H
