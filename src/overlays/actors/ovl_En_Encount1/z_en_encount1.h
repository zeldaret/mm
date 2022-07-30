#ifndef Z_EN_ENCOUNT1_H
#define Z_EN_ENCOUNT1_H

#include "global.h"

#define ENENCOUNT1_GET_3F(thisx) ((thisx)->params & 0x3F)

struct EnEncount1;

typedef void (*EnEncount1ActionFunc)(struct EnEncount1*, PlayState*);

typedef struct EnEncount1 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnEncount1ActionFunc actionFunc;
    /* 0x148 */ Path* unk148;
    /* 0x14C */ s16 unk14C;
    /* 0x14E */ s16 unk_14E;
    /* 0x150 */ s16 unk150;
    /* 0x152 */ s16 unk152;
    /* 0x154 */ s16 unk154;
    /* 0x156 */ s16 unk156;
    /* 0x158 */ s16 unk158;
    /* 0x15A */ s16 unk_15A;
    /* 0x15C */ s32 unk15C;
    /* 0x160 */ f32 unk160;
} EnEncount1; // size = 0x164

extern const ActorInit En_Encount1_InitVars;

#endif // Z_EN_ENCOUNT1_H
