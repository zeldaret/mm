#ifndef Z_EN_LIFT_NUTS_H
#define Z_EN_LIFT_NUTS_H

#include "global.h"
#include "objects/object_dnt/object_dnt.h"

struct EnLiftNuts;

typedef void (*EnLiftNutsActionFunc)(struct EnLiftNuts*, PlayState*);

#define ENLIFTNUTS_GET_FF00(thisx) (((thisx)->params & 0xFF00) >> 8)

typedef struct EnLiftNuts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ SkelAnime skelAnime;
    /* 0x1D4 */ EnLiftNutsActionFunc actionFunc;
    /* 0x1D8 */ Vec3f vec_1D8;
    /* 0x1E4 */ s32 unk_1E4;
    /* 0x1E8 */ s32 unk_1E8;
    /* 0x1EC */ s16* ptr_1EC;
    /* 0x1F0 */ Vec3s jointTable[OBJECT_DNT_LIMB_MAX];
    /* 0x298 */ Vec3s morphTable[OBJECT_DNT_LIMB_MAX];
    /* 0x340 */ UNK_TYPE1 unk_340[0xC];
    /* 0x34C */ s16 textId;
    /* 0x34E */ s16 unk_34E;
    /* 0x350 */ UNK_TYPE1 unk_350[0x4];
    /* 0x354 */ s16 unk_354;
    /* 0x356 */ s16 unk_356;
} EnLiftNuts; // size = 0x358

#endif // Z_EN_LIFT_NUTS_H
