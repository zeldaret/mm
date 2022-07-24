#ifndef Z_EN_HG_H
#define Z_EN_HG_H

#include "global.h"
#include "objects/object_harfgibud/object_harfgibud.h"


struct EnHg;

typedef void (*EnHgActionFunc)(struct EnHg*, PlayState*);

typedef struct EnHg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ SkelAnime skelAnime;
    /* 0x1D4 */ EnHgActionFunc actionFunc;
    /* 0x1D8 */ MtxF unk1D8;
    /* 0x218 */ s32 unk218;
    /* 0x21C */ s32 currentAnimation;
    /* 0x220 */ Vec3s jointTable[HARFGIBUD_GIBDO_LIMB_MAX];
    /* 0x292 */ Vec3s morphTable[HARFGIBUD_GIBDO_LIMB_MAX];
    /* 0x304 */ UNK_TYPE1 pad304[0xC];
    /* 0x310 */ u16 cutscenes[4];
} EnHg; // size = 0x318

extern const ActorInit En_Hg_InitVars;

#endif // Z_EN_HG_H
