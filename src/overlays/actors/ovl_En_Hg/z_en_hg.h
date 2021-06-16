#ifndef Z_EN_HG_H
#define Z_EN_HG_H

#include <global.h>

struct EnHg;

typedef void (*EnHgActionFunc)(struct EnHg*, GlobalContext*);

typedef struct EnHg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider; // size = 0x4C
    /* 0x190 */ SkelAnime skelAnime; // size = 0x44
    /* 0x1D4 */ EnHgActionFunc actionFunc;
    /* 0x1D8 */ MtxF unk1D8;
    /* 0x218 */ s32 unk_218;
    /* 0x21C */ s32 unk21C;
    /* 0x220 */ Vec3s limbDrawTbl[19]; // size = 0x72
    /* 0x292 */ Vec3s transitionDrawTbl[19]; // size = 0x72
    /* 0x304 */ char pad304[0xC];
    /* 0x310 */ u16 unk310[4];
} EnHg; // size = 0x318

extern const ActorInit En_Hg_InitVars;

#endif // Z_EN_HG_H
