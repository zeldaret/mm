#ifndef Z_OBJ_SNOWBALL2_H
#define Z_OBJ_SNOWBALL2_H

#include "global.h"

struct ObjSnowball2;

typedef void (*ObjSnowball2ActionFunc)(struct ObjSnowball2*, GlobalContext*);

#define ENOBJSNOWBALL2_GET_3F(thisx) ((thisx)->params & 0x3F)
#define ENOBJSNOWBALL2_GET_7F00(thisx) (((thisx)->params >> 8) & 0x7F)

typedef struct ObjSnowball2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderJntSph collider;
    /* 0x0164 */ ColliderJntSphElement colliderElements[1];
    /* 0x01A4 */ ObjSnowball2ActionFunc actionFunc;
    /* 0x01A8 */ s16 unk_1A8;
    /* 0x01AA */ s16 unk_1AA;
    /* 0x01AC */ s8 unk_1AC;
    /* 0x01AD */ u8 unk_1AD;
    /* 0x01AE */ s8 unk_1AE;
    /* 0x01AF */ s8 unk_1AF;
    /* 0x01B0 */ UNK_TYPE1 unk1B0[4];
} ObjSnowball2; // size = 0x1B4

extern const ActorInit Obj_Snowball2_InitVars;

#endif // Z_OBJ_SNOWBALL2_H
