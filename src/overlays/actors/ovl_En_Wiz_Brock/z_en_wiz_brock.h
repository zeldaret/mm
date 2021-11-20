#ifndef Z_EN_WIZ_BROCK_H
#define Z_EN_WIZ_BROCK_H

#include "global.h"

struct EnWizBrock;

typedef void (*EnWizBrockActionFunc)(struct EnWizBrock*, GlobalContext*);

typedef struct EnWizBrock {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x5C];
    /* 0x01A0 */ EnWizBrockActionFunc actionFunc;
    /* 0x01A4 */ char unk_1A4[0xC];
} EnWizBrock; // size = 0x1B0

extern const ActorInit En_Wiz_Brock_InitVars;

#endif // Z_EN_WIZ_BROCK_H
