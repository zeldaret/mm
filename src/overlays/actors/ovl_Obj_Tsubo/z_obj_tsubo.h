#ifndef Z_OBJ_TSUBO_H
#define Z_OBJ_TSUBO_H

#include "global.h"

struct ObjTsubo;

typedef void (*ObjTsuboActionFunc)(struct ObjTsubo*, GlobalContext*);

typedef void (*ObjTsuboUnkFunc)(struct ObjTsubo* this, GlobalContext* globalCtx);

typedef struct ObjTsubo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjTsuboActionFunc actionFunc;
    /* 0x0148 */ ColliderCylinder cylinderCollider;
    /* 0x0194 */ s8 unk194;
    /* 0x0195 */ s8 unk195;
    /* 0x0196 */ s8 homeRoom;
    /* 0x0197 */ s8 unk197;
    /* 0x0198 */ s8 unk198;
    /* 0x0199 */ s8 objBankIdx;
    /* 0x019A */ s8 unk19A;
    /* 0x019B */ u8 pad19B;

} ObjTsubo; // size = 0x19C

extern const ActorInit Obj_Tsubo_InitVars;

typedef enum {
    OBJ_TSUBO_TYPE_0,
    OBJ_TSUBO_TYPE_1,
    OBJ_TSUBO_TYPE_2,
    OBJ_TSUBO_TYPE_3,
} ObjTsuboType;

#define OBJ_TSUBO_P000F(thisx) ((thisx)->params & 0x0F)
#define OBJ_TSUBO_P001F(thisx) ((thisx)->params & 0x1F)
#define OBJ_TSUBO_P003F(thisx) ((thisx)->params & 0x3F)
#define OBJ_TSUBO_P0010(thisx) (((thisx)->params >> 4) & 1)
#define OBJ_TSUBO_GET_TYPE(thisx) (((thisx)->params >> 7) & 3)
#define OBJ_TSUBO_PFE00(thisx) (((thisx)->params >> 9) & 0x7F) //item collectable flag?
#define OBJ_TSUBO_ZROT(thisx) ((thisx)->home.rot.z)

#endif // Z_OBJ_TSUBO_H
