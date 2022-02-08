#ifndef Z_BG_INGATE_H
#define Z_BG_INGATE_H

#include "global.h"

struct BgIngate;

typedef void (*BgIngateActionFunc)(struct BgIngate*, GlobalContext*);

#define BGINGATE_GET_FF(thisx) ((thisx)->params & 0xFF)

typedef struct BgIngate {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ BgIngateActionFunc actionFunc;
    /* 0x160 */ u16 unk160;
    /* 0x164 */ Path* unk164;
    /* 0x168 */ s16 unk168;
    /* 0x16A */ s16 unk16A;
    /* 0x16C */ s16 unk16C;
    /* 0x16E */ s16 unk16E;
    /* 0x170 */ Vec3f unk170;
    /* 0x17C */ f32 unk17C;
    /* 0x180 */ s32 unk180;
    /* 0x184 */ s32 unk184;
    /* 0x188 */ s32 unk188;
    /* 0x18C */ s32 unk18C;
} BgIngate; // size = 0x190

extern const ActorInit Bg_Ingate_InitVars;

#endif // Z_BG_INGATE_H
