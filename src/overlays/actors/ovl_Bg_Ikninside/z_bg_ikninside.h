#ifndef Z_BG_IKNINSIDE_H
#define Z_BG_IKNINSIDE_H

#include "global.h"

struct BgIkninside;

typedef void (*BgIkninsideActionFunc)(struct BgIkninside*, GlobalContext*);

typedef struct BgIkninside {
    /* 0x000 */ Actor actor;
    /* 0x144 */ s32 unk144;                         /* inferred */
    /* 0x148 */ char pad148[0x14];                  /* maybe part of unk144[6]? */
    /* 0x15C */ ColliderCylinder unk15C;            /* inferred */
    /* 0x1A8 */ char pad1A8[4];
    /* 0x01AC */ BgIkninsideActionFunc actionFunc;
} BgIkninside; // size = 0x1B0

extern const ActorInit Bg_Ikninside_InitVars;

#endif // Z_BG_IKNINSIDE_H
