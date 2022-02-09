#ifndef Z_OBJ_KZSAKU_H
#define Z_OBJ_KZSAKU_H

#include "global.h"

#define KZSAKU_GET_SWITCHFLAG(thisx) (((thisx)->params & 0x7F00) >> 8)

struct ObjKzsaku;

typedef void (*ObjKzsakuActionFunc)(struct ObjKzsaku*, GlobalContext*);

typedef struct ObjKzsaku {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ ObjKzsakuActionFunc actionFunc;
    /* 0x0160 */ f32 raisedAmount;
    /* 0x0164 */ s32 switchFlag;
    /* 0x0168 */ s16 timer;
} ObjKzsaku; // size = 0x16C

extern const ActorInit Obj_Kzsaku_InitVars;

#endif // Z_OBJ_KZSAKU_H
