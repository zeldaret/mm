#ifndef Z_EN_FALL_H
#define Z_EN_FALL_H

#include "global.h"

#define EN_FALL_TYPE1(thisx) ((thisx)->params & 0x7F)
#define EN_FALL_TYPE2(thisx) (((thisx)->params & 0xF80) >> 7)

struct EnFall;

typedef void (*EnFallActionFunc)(struct EnFall*, GlobalContext*);

typedef struct EnFall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
    /* 0x148 */ s8 unk_148;
    /* 0x149 */ char unk_149[0x3];
    /* 0x14C */ f32 unk_14C;
    /* 0x150 */ f32 unk_150;
    /* 0x154 */ s16 unk_154;
    /* 0x156 */ char unk_156[0xA];
    /* 0x160 */ EnFallActionFunc actionFunc;
} EnFall; // size = 0x164

extern const ActorInit En_Fall_InitVars;

#endif // Z_EN_FALL_H
