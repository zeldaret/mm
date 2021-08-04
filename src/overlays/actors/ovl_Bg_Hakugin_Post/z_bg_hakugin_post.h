#ifndef Z_BG_HAKUGIN_POST_H
#define Z_BG_HAKUGIN_POST_H

#include "global.h"

struct BgHakuginPost;

typedef void (*BgHakuginPostActionFunc)(struct BgHakuginPost* this, GlobalContext* globalCtx);

typedef struct BgHakuginPost {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ BgHakuginPostActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x28];
} BgHakuginPost; // size = 0x188

extern const ActorInit Bg_Hakugin_Post_InitVars;

#endif // Z_BG_HAKUGIN_POST_H
