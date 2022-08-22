#ifndef Z_EN_M_THUNDER_H
#define Z_EN_M_THUNDER_H

#include "global.h"

struct EnMThunder;

#define ENMTHUNDER_GET_UNK1BF(thisx) ((thisx)->params & 0xFF)
#define ENMTHUNDER_GET_MAGIC_COST(thisx) (((thisx)->params & 0xFF00) >> 8)

typedef void (*EnMThunderActionFunc)(struct EnMThunder*, PlayState*);

typedef struct EnMThunder {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ LightNode* lightNode;
    /* 0x194 */ LightInfo lightInfo;
    /* 0x1A4 */ f32 unk1A4; // ligh color scale/proportion
    /* 0x1A8 */ f32 unk1A8; // some alpha scale/proportion
    /* 0x1AC */ f32 unk1AC; // scroll param
    /* 0x1B0 */ f32 unk1B0; // same as unk_B08[0] (should be just unk_B08)
    /* 0x1B4 */ f32 unk1B4; // func_800FD2B4 arg1
    /* 0x1B8 */ EnMThunderActionFunc actionFunc;
    /* 0x1BC */ u16 unk1BC; // timer of some kind
    /* 0x1BE */ u8 unk1BE; // choses sound/graphics
    /* 0x1BF */ u8 unk1BF; // type? comes from params
    /* 0x1C0 */ u8 unk1C0; // alpha of some kind
    /* 0x1C1 */ u8 unk1C1; // scaleTarget
    /* 0x1C2 */ u8 unk1C2; // boolean
} EnMThunder; // size = 0x1C4

extern const ActorInit En_M_Thunder_InitVars;

#endif // Z_EN_M_THUNDER_H
