#ifndef Z_EN_M_THUNDER_H
#define Z_EN_M_THUNDER_H

#include "global.h"

struct EnMThunder;

#define ENMTHUNDER_GET_UNK1BF(thisx) ((thisx)->params & 0xFF)
#define ENMTHUNDER_GET_MAGIC_COST(thisx) (((thisx)->params & 0xFF00) >> 8)

typedef void (*EnMThunderActionFunc)(struct EnMThunder*, PlayState*);

typedef struct EnMThunder {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder unk144;
    /* 0x190 */ LightNode* unk190;
    /* 0x194 */ LightInfo unk194;
    /* 0x1A2 */ char pad1A2[2];
    /* 0x1A4 */ f32 unk1A4;
    /* 0x1A8 */ f32 unk1A8;
    /* 0x1AC */ f32 unk1AC;
    /* 0x1B0 */ f32 unk1B0;
    /* 0x1B4 */ f32 unk1B4;
    /* 0x1B8 */ EnMThunderActionFunc actionFunc;
    /* 0x1BC */ u16 unk1BC;
    /* 0x1BE */ u8 unk1BE;
    /* 0x1BF */ u8 unk1BF;
    /* 0x1C0 */ u8 unk1C0;
    /* 0x1C1 */ u8 unk1C1;
    /* 0x1C2 */ u8 unk1C2;
    /* 0x1C3 */ char pad1C3[1];
} EnMThunder; // size = 0x1C4

extern const ActorInit En_M_Thunder_InitVars;

#endif // Z_EN_M_THUNDER_H
