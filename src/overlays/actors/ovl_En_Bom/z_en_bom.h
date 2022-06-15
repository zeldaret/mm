#ifndef Z_EN_BOM_H
#define Z_EN_BOM_H

#include "global.h"

struct EnBom;

typedef void (*EnBomActionFunc)(struct EnBom*, GlobalContext*);

#define ENBOM_GETX_1(thisx) ((thisx)->shape.rot.x & 1)
#define ENBOM_GETZ_80(thisx) ((thisx)->shape.rot.z & 0x80)
#define ENBOM_GETZ_FF00(thisx) (((thisx)->shape.rot.z & 0xFF00) >> 8)

enum {
    /* 0 */ ENBOM_0,
    /* 1 */ ENBOM_1,
};

typedef struct EnBom {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider1;
    /* 0x190 */ ColliderJntSph collider2;
    /* 0x1B0 */ ColliderJntSphElement collider3;
    /* 0x1F0 */ s16 timer;
    /* 0x1F2 */ s16 flashSpeedScale;
    /* 0x1F4 */ f32 unk_1F4;
    /* 0x1F8 */ u8 unk_1F8;
    /* 0x1F9 */ u8 isPowderKeg;
    /* 0x1FA */ s16 unk_1FA;
    /* 0x1FC */ u8 unk_1FC;
    /* 0x200 */ EnBomActionFunc actionFunc;
} EnBom; // size = 0x204

extern const ActorInit En_Bom_InitVars;

#endif // Z_EN_BOM_H
