#ifndef Z_BG_HAKUGIN_ELVPOLE_H
#define Z_BG_HAKUGIN_ELVPOLE_H

#include "global.h"

struct BgHakuginElvpole;

typedef void (*BgHakuginElvpoleActionFunc)(struct BgHakuginElvpole* this, GlobalContext* globalCtx);

typedef struct BgHakuginElvpole {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x20];
    /* 0x0164 */ BgHakuginElvpoleActionFunc actionFunc;
} BgHakuginElvpole; // size = 0x168

extern const ActorInit Bg_Hakugin_Elvpole_InitVars;

#endif // Z_BG_HAKUGIN_ELVPOLE_H
