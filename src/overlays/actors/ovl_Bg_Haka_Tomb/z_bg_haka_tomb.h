#ifndef Z_BG_HAKA_TOMB_H
#define Z_BG_HAKA_TOMB_H

#include <global.h>

struct BgHakaTomb;

typedef void (*BgHakaTombActionFunc)(struct BgHakaTomb*, GlobalContext*);

typedef struct BgHakaTomb {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ BgHakaTombActionFunc actionFunc;
    /* 0x160 */ s16 unk160[2];
} BgHakaTomb; // size = 0x164

extern const ActorInit Bg_Haka_Tomb_InitVars;

#endif // Z_BG_HAKA_TOMB_H
