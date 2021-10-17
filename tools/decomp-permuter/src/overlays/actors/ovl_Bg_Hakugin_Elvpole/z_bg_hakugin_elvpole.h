#ifndef Z_BG_HAKUGIN_ELVPOLE_H
#define Z_BG_HAKUGIN_ELVPOLE_H

#include <global.h>

struct BgHakuginElvpole;

typedef struct BgHakuginElvpole {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x24];
} BgHakuginElvpole; // size = 0x168

extern const ActorInit Bg_Hakugin_Elvpole_InitVars;

#endif // Z_BG_HAKUGIN_ELVPOLE_H
