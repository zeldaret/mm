#ifndef Z_BG_SINKAI_KABE_H
#define Z_BG_SINKAI_KABE_H

#include "global.h"
#include "overlays/actors/ovl_En_Dragon/z_en_dragon.h"

struct BgSinkaiKabe;

typedef void (*BgSinkaiKabeActionFunc)(struct BgSinkaiKabe*, GlobalContext*);

typedef struct BgSinkaiKabe {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ BgSinkaiKabeActionFunc actionFunc;
    /* 0x160 */ Actor* deepPythonChild;
    /* 0x164 */ s16 cutscenes[4]; // only the first two are ever used. size is inferred based on context
    /* 0x16C */ s32 pythonIndex;
} BgSinkaiKabe; // size = 0x170

extern const ActorInit Bg_Sinkai_Kabe_InitVars;

#endif // Z_BG_SINKAI_KABE_H
