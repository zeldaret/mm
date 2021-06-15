#ifndef Z_BG_IKNIN_SUSCEIL_H
#define Z_BG_IKNIN_SUSCEIL_H

#include <global.h>

struct BgIkninSusceil;

typedef void (*BgIkninSusceilActionFunc)(struct BgIkninSusceil*, GlobalContext*);

typedef struct BgIkninSusceil {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ AnimatedMaterial* unk15C;
    /* 0x160 */ BgIkninSusceilActionFunc actionFunc;
    /* 0x164 */ s16 unk164;
    /* 0x166 */ s16 unk166;
    /* 0x168 */ s16 unk168;
} BgIkninSusceil; // size = 0x16C

extern const ActorInit Bg_Iknin_Susceil_InitVars;

#endif // Z_BG_IKNIN_SUSCEIL_H
