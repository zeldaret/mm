#ifndef Z_EN_FG_H
#define Z_EN_FG_H

#include <global.h>

struct EnFg;

typedef void (*EnFgActionFunc)(struct EnFg*, GlobalContext*);

typedef struct {
    /* 0x0000 */ u8 type;
    /* 0x0001 */ u8 timer;
    /* 0x0004 */ f32 xyScale;
    /* 0x0008 */ char unk_08[0xC];
    /* 0x0014 */ Vec3f pos;
    /* 0x0020 */ Vec3f accel;
    /* 0x002C */ Vec3f velocity;
    /* 0x0038 */ char unk_38[0x4];
} EnFgUnkEffect; // size = 0x3C

typedef struct EnFg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnFgActionFunc actionFunc;
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ Vec3s limbDrawTbl[24];
    /* 0x268 */ Vec3s transitionDrawTbl[24];
    /* 0x2F8 */ s16 unk_2F8;
    /* 0x2FA */ s16 unk_2FA;
    /* 0x2FC */ EnFgUnkEffect unkEffect[10];
} EnFg; // size = 0x554

extern const ActorInit En_Fg_InitVars;

#endif // Z_EN_FG_H
