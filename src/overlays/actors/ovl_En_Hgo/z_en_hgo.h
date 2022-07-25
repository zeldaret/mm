#ifndef Z_EN_HGO_H
#define Z_EN_HGO_H

#include "global.h"
#include "objects/object_harfgibud/object_harfgibud.h"

struct EnHgo;

typedef void (*EnHgoActionFunc)(struct EnHgo*, PlayState*);

typedef struct EnHgo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ SkelAnime skelAnime;
    /* 0x1D4 */ EnHgoActionFunc actionFunc;
    /* 0x1D8 */ MtxF unk_1D8;
    /* 0x218 */ s32 unk_218;
    /* 0x21C */ Vec3s jointTable[HARFGIBUD_HUMAN_LIMB_MAX];
    /* 0x28E */ Vec3s morphTable[HARFGIBUD_HUMAN_LIMB_MAX];
    /* 0x300 */ Vec3s headRot;
    /* 0x306 */ Vec3s torsoRot; // Set, but not used
    /* 0x30C */ s16 unk_30C;
    /* 0x30E */ s16 unk_30E;
    /* 0x310 */ s16 unk_310;
    /* 0x312 */ s16 unk_312;
    /* 0x314 */ u16 unk_314;
    /* 0x316 */ u16 unk_316;
} EnHgo; // size = 0x318

extern const ActorInit En_Hgo_InitVars;

#endif // Z_EN_HGO_H
