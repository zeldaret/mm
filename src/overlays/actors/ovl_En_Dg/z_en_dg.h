#ifndef Z_EN_DG_H
#define Z_EN_DG_H

#include "global.h"
#include "objects/object_dog/object_dog.h"

struct EnDg;

typedef void (*EnDgActionFunc)(struct EnDg*, GlobalContext*);

#define ENDG_GET_FC00(thisx) (((thisx)->params & 0xFC00) >> 0xA)
#define ENDG_GET_3E0(thisx) (((thisx)->params & 0x3E0) >> 5)

typedef struct EnDg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnDgActionFunc actionFunc;
    /* 0x148 */ UNK_TYPE1 unk_148[0x4];
    /* 0x14C */ SkelAnime skelAnime;
    /* 0x190 */ ColliderCylinder collider;
    /* 0x1DC */ Path* unk_1DC;
    /* 0x1E0 */ s32 unk_1E0;
    /* 0x1E4 */ Vec3s jointTable[DOG_LIMB_MAX];
    /* 0x232 */ Vec3s morphTable[DOG_LIMB_MAX];
    /* 0x280 */ u16 unk_280;
    /* 0x282 */ s16 unk_282;
    /* 0x284 */ s16 unk_284;
    /* 0x286 */ s16 unk_286;
    /* 0x288 */ s16 unk_288;
    /* 0x28A */ s16 unk_28A;
    /* 0x28C */ s16 unk_28C;
    /* 0x28E */ s16 unk_28E;
    /* 0x290 */ s16 unk_290;
    /* 0x292 */ s16 unk_292;
    /* 0x294 */ Vec3f unk_294;
} EnDg; // size = 0x2A0

extern const ActorInit En_Dg_InitVars;

#endif // Z_EN_DG_H
