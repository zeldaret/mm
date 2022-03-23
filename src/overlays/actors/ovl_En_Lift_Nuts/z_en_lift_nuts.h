#ifndef Z_EN_LIFT_NUTS_H
#define Z_EN_LIFT_NUTS_H

#include "global.h"

struct EnLiftNuts;

typedef void (*EnLiftNutsActionFunc)(struct EnLiftNuts*, GlobalContext*);

typedef struct EnLiftNuts {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ SkelAnime skelAnime;
    /* 0x01D4 */ EnLiftNutsActionFunc actionFunc;
    /* 0x01D8 */ Vec3f vec_1D8;
    /* 0x01E4 */ s32 unk_1E4;
    /* 0x01E8 */ s32 unk_1E8;
    /* 0x01EC */ s16* ptr_1EC;
    /* 0x01F0 */ Vec3s jointTable[28];
    /* 0x0298 */ Vec3s morphTable[28];
    /* 0x0340 */ char unk_340[0xC];
    /* 0x034C */ u16 textId;
    /* 0x034E */ s16 unk_34E;
    /* 0x0350 */ char unk_350[0x4];
    /* 0x0354 */ s16 unk_354;
    /* 0x0356 */ s16 unk_356;
} EnLiftNuts; // size = 0x358

extern const ActorInit En_Lift_Nuts_InitVars;

#endif // Z_EN_LIFT_NUTS_H
