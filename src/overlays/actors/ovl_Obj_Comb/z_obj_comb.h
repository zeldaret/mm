#ifndef Z_OBJ_COMB_H
#define Z_OBJ_COMB_H

#include "global.h"

struct ObjComb;

typedef void (*ObjCombActionFunc)(struct ObjComb*, GlobalContext*);

#define OBJCOMB_GET_F(thisx) ((thisx)->params & 0xF)
#define OBJCOMB_GET_10(thisx) (((thisx)->params >> 4) & 0x1)
#define OBJCOMB_GET_1F(thisx) ((thisx)->params & 0x1F)
#define OBJCOMB_GET_3F(thisx) ((thisx)->params & 0x3F)
#define OBJCOMB_GET_80(thisx) (((thisx)->params >> 7) & 0x1)
#define OBJCOMB_GET_7F00(thisx) (((thisx)->params >> 0x8) & 0x7F)
#define OBJCOMB_GET_8000(thisx) (((thisx)->params >> 0xE) & 2)

typedef struct ObjComb {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjCombActionFunc actionFunc;
    /* 0x0148 */ ColliderJntSph collider;
    /* 0x0168 */ ColliderJntSphElement colliderElement;
    /* 0x01A8 */ s16 unk_1A8;
    /* 0x01AA */ s16 unk_1AA;
    /* 0x01AC */ s16 unk_1AC;
    /* 0x01AE */ s16 unk_1AE;
    /* 0x01B0 */ s16 unk_1B0;
    /* 0x01B2 */ s8 unk_1B2;
    /* 0x01B3 */ s8 unk_1B3;
    /* 0x01B4 */ s8 unk_1B4;
    /* 0x01B5 */ s8 unk_1B5;
    /* 0x01B6 */ s8 unk_1B6;
    /* 0x01B7 */ s8 unk_1B7;
    /* 0x01B8 */ s8 unk_1B8;
} ObjComb; // size = 0x1BC

extern const ActorInit Obj_Comb_InitVars;

#endif // Z_OBJ_COMB_H
