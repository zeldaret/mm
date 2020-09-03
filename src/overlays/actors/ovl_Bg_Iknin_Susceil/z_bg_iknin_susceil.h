#ifndef _Z_BG_IKNIN_SUSCEIL_H_
#define _Z_BG_IKNIN_SUSCEIL_H_

#include <global.h>

struct BgIkninSusceil;

typedef struct BgIkninSusceil {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x28];
} BgIkninSusceil; // size = 0x16C

extern const ActorInit Bg_Iknin_Susceil_InitVars;

#endif
