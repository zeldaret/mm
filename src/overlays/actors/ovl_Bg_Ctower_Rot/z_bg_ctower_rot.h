#ifndef Z_BG_CTOWER_ROT_H
#define Z_BG_CTOWER_ROT_H

#include <global.h>

struct BgCtowerRot;

typedef void (*BgCtowerRotActionFunc)(struct BgCtowerRot*, GlobalContext*);

typedef struct BgCtowerRot {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ BgCtowerRotActionFunc actionFunc;
    /* 0x160 */ f32 unk160; //Set to 0 but never used
    /* 0x164 */ f32 timer;
} BgCtowerRot; // size = 0x168

extern const ActorInit Bg_Ctower_Rot_InitVars;

#endif // Z_BG_CTOWER_ROT_H
