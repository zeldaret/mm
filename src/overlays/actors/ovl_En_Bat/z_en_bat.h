#ifndef Z_EN_BAT_H
#define Z_EN_BAT_H

#include "global.h"

#define BAT_GET_TYPE(thisx) (((thisx)->params >> 0) & 0x1F)
#define BAT_GET_E0(thisx) (((thisx)->params >> 5) & 7)
#define BAT_GET_SWITCHFLAG(thisx) (((thisx)->params >> 8) & 0xFF)
#define BAT_PARAMS(switchFlag, e0, type) ((type) | ((e0) << 5) | ((switchFlag) << 8))

struct EnBat;

typedef void (*EnBatActionFunc)(struct EnBat*, PlayState*);

typedef struct EnBat {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnBatActionFunc actionFunc;
    /* 0x148 */ u8 drawDmgEffType;
    /* 0x149 */ u8 paramsE0;
    /* 0x14A */ s16 switchFlag;
    /* 0x14C */ s16 unk14C;
    /* 0x14E */ s16 unk14E;
    /* 0x150 */ s16 unk150;
    /* 0x152 */ s16 unk152;
    /* 0x154 */ f32 drawDmgEffScale;
    /* 0x158 */ f32 drawDmgEffFrozenSteamScale;
    /* 0x15C */ f32 drawDmgEffAlpha;
    /* 0x160 */ Vec3f bodyPartPoss[3];
    /* 0x184 */ ColliderSphere collider;
} EnBat; // size = 0x1DC

extern const ActorInit En_Bat_InitVars;

#endif // Z_EN_BAT_H
