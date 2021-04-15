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
    /* 0x164 */ UNK_TYPE1 unk164[0x40];
    /* 0x1A4 */ ObjLightswitchActionFunc actionFunc;
    /* 0x1A8 */ s16 unk1A8;
    /* 0x1AA */ s16 unk1AA;
    /* 0x1AC */ s16 unk1AC;
    /* 0x1AE */ s16 unk1AE;
    /* 0x1B0 */ s16 unk1B0;
    /* 0x1B2 */ s16 unk1B2;
    /* 0x1B4 */ s8 unk1B4;
    /* 0x1B5 */ s8 unk1B5;
    /* 0x1B6 */ s8 unk1B6;
    /* 0x1B7 */ u8 pad1B7;
    /* 0x1B8 */ ObjLightswitchSetupFunc setupFunc; // func_8096034C type
    /* 0x1BC */ s8 unk1BC;
    /* 0x1BD */ s8 unk1BD;
    ///* 0x1BD */ s8 unk1BD;
    ///* 0x1BD */ s8 unk1BD;

} ObjLightswitch; // size = 0x1C0

extern const ActorInit Obj_Lightswitch_InitVars;

extern s32 D_80960BD8;//init chain

extern s32 D_80960BF0; // 6.127451e-05


#endif // Z_OBJ_LIGHTSWITCH_H
