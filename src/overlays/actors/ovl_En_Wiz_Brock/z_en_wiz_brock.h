#ifndef Z_EN_WIZ_BROCK_H
#define Z_EN_WIZ_BROCK_H

#include "global.h"

struct EnWizBrock;

typedef void (*EnWizBrockActionFunc)(struct EnWizBrock*, GlobalContext*);

typedef struct EnWizBrock {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ char unk_15C[0x44];
    /* 0x01A0 */ EnWizBrockActionFunc actionFunc;
    /* 0x1A4 */ s16 unk1A4;
    /* 0x1A6 */ s16 unk1A6;
    /* 0x1A8 */ s16 unk1A8;
    /* 0x1AA */ s16 unk1AA;
    /* 0x1AC */ f32 alpha;
} EnWizBrock; // size = 0x1B0

extern const ActorInit En_Wiz_Brock_InitVars;

#endif // Z_EN_WIZ_BROCK_H
