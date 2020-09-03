#ifndef Z_BG_HAKUGIN_POST_H
#define Z_BG_HAKUGIN_POST_H

#include <global.h>

struct BgHakuginPost;

typedef struct BgHakuginPost {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x44];
} BgHakuginPost; // size = 0x188

extern const ActorInit Bg_Hakugin_Post_InitVars;

#endif // Z_BG_HAKUGIN_POST_H
