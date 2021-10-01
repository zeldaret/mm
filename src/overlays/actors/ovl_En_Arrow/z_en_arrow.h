#ifndef Z_EN_ARROW_H
#define Z_EN_ARROW_H

#include "global.h"

struct EnArrow;

typedef void (*EnArrowActionFunc)(struct EnArrow*, GlobalContext*);

typedef struct EnArrow {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x7C];
    /* 0x01C0 */ s32 unk_1C0;
    /* 0x01C4 */ char unk_1C4[0x9C];
    /* 0x0260 */ u8 unk_260; // timer in OoT
    /* 0x0261 */ u8 unk_261; // hitFlags in OoT
    /* 0x0262 */ char unk_262[0x12];
    /* 0x0274 */ EnArrowActionFunc actionFunc;
} EnArrow; // size = 0x278

extern const ActorInit En_Arrow_InitVars;

#endif // Z_EN_ARROW_H
