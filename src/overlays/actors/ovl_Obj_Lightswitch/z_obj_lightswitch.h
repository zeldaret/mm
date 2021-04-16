#ifndef Z_OBJ_LIGHTSWITCH_H
#define Z_OBJ_LIGHTSWITCH_H

#include <global.h>

typedef void (*ObjLightswitchActionFunc)(struct ObjLightswitch*, GlobalContext*);
typedef void (*ObjLightswitchSetupFunc)(struct ObjLightswitch*);

struct ObjLightswitch;

typedef struct ObjLightswitch {
    /* 0x000 */ Actor actor;
    ///* 0x144 */ char unk_144[0x7C];
    /* 0x144 */ ColliderJntSph collider;
    /* 0x164 */ ColliderJntSphElement elements;
    /* 0x1A4 */ ObjLightswitchActionFunc actionFunc;
    /* 0x1A8 */ s16 colorValue1; // used in opa/xlu funcs
    /* 0x1AA */ s16 colorValue2;
    /* 0x1AC */ s16 colorValue3;
    /* 0x1AE */ s16 colorValue4;
    /* 0x1B0 */ s16 zRotOffset; // used in opa/xlu funcs
    /* 0x1B2 */ s16 zRotIncr;
    /* 0x1B4 */ s8 colorShiftTimer;
    /* 0x1B5 */ s8 unk1B5; // mixed use timer?
    /* 0x1B6 */ s8 segmentIndex; // polyopa/xlu segment address index
    /* 0x1B7 */ u8 previousACFlags;
    /* 0x1B8 */ ObjLightswitchSetupFunc setupFunc;
    /* 0x1BC */ s8 switchFlagSetType; // 1 or 0 , for set or unset flags
    /* 0x1BD */ s8 cutsceneTimer;

} ObjLightswitch; // size = 0x1C0

extern const ActorInit Obj_Lightswitch_InitVars;

// opa func
extern s32 D_801AEFA0;

// xlu func
extern s32 D_801AEF88;

#define LIGHTSWITCH_TYPE_FLAT 0
#define LIGHTSWITCH_TYPE_FLIP 1
#define LIGHTSWITCH_TYPE_UNK2 2
#define LIGHTSWITCH_TYPE_ANIMATED_FACE 3


#define GET_LIGHTSWITCH_TYPE(this) (((this)->actor.params >> 4) & 0x3)
#define GET_LIGHTSWITCH_INVISIBLE(this) (((this)->actor.params >> 3) & 1)
#define GET_LIGHTSWITCH_SWITCHFLAG(this) (((this)->actor.params >> 8) & 0x7F)

#endif // Z_OBJ_LIGHTSWITCH_H
