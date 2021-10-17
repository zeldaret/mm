#ifndef Z_BG_UMAJUMP_H
#define Z_BG_UMAJUMP_H

#include <global.h>

struct BgUmajump;

typedef struct BgUmajump {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x28];
} BgUmajump; // size = 0x16C

extern const ActorInit Bg_Umajump_InitVars;

#endif // Z_BG_UMAJUMP_H
