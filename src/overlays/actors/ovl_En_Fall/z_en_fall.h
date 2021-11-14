#ifndef Z_EN_FALL_H
#define Z_EN_FALL_H

#include "global.h"

#define EN_FALL_SCALE(thisx) ((thisx)->params & 0x7F)
#define EN_FALL_TYPE(thisx) (((thisx)->params & 0xF80) >> 7)

struct EnFall;

typedef void (*EnFallActionFunc)(struct EnFall*, GlobalContext*);

typedef struct EnFall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ s16 unk_144;
    /* 0x146 */ s16 unk_146;
    /* 0x148 */ u8 unk_148;
    /* 0x149 */ char unk_149[0x3];
    /* 0x14C */ f32 unk_14C;
    /* 0x150 */ f32 unk_150;
    /* 0x154 */ u16 unk_154;
    /* 0x156 */ char unk_156[0x2];
    /* 0x158 */ s32 unk_158;
    /* 0x15C */ s16 unk_15C;
    /* 0x15E */ char unk_15E[0x2];
    /* 0x160 */ EnFallActionFunc actionFunc;
} EnFall; // size = 0x164

extern const ActorInit En_Fall_InitVars;

#endif // Z_EN_FALL_H
