#ifndef Z_BG_HAKA_CURTAIN_H
#define Z_BG_HAKA_CURTAIN_H

#include <global.h>

struct BgHakaCurtain;

typedef struct BgHakaCurtain {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1C];
} BgHakaCurtain; // size = 0x160

extern const ActorInit Bg_Haka_Curtain_InitVars;

#endif // Z_BG_HAKA_CURTAIN_H
