#ifndef Z_EN_FG_H
#define Z_EN_FG_H

#include <global.h>

struct EnFg;

typedef void (*EnFgActionFunc)(struct EnFg*, GlobalContext*);

typedef struct EnFg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnFgActionFunc actionFunc;
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ Vec3s limbDrawTbl[24];
    /* 0x268 */ Vec3s transitionDrawTbl[24];
    /* 0x2F8 */ s16 unk_2F8;
    /* 0x2FA */ s16 unk_2FA;
    /* 0x2FC */ PosRot unk_2FC;
    /* 0x310 */ char unk_300[0x24C];
} EnFg; // size = 0x554

extern const ActorInit En_Fg_InitVars;

#endif // Z_EN_FG_H
