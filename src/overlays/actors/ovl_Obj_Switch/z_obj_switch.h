#ifndef Z_OBJ_SWITCH_H
#define Z_OBJ_SWITCH_H

#include "global.h"

struct ObjSwitch;

typedef void (*ObjSwitchActionFunc)(struct ObjSwitch* this, GlobalContext* globalCtx);
typedef void (*ObjSwitchDrawFunc)(struct ObjSwitch* this, GlobalContext* globalCtx);
typedef void (*ObjSwitchSetupActionFunc)(struct ObjSwitch* this);

typedef struct ObjSwitch {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ ObjSwitchActionFunc actionFunc;
    /* 0x0160 */ s16 unk_160;
    /* 0x0162 */ s16 unk_162;
    /* 0x0164 */ s8 unk_164;
    /* 0x0165 */ s8 unk_165;
    /* 0x0168 */ s32 unk_168;
    /* 0x016C */ u8 unk_16C;
    /* 0x016D */ u8 unk_16D;
    /* 0x016E */ u8 unk_16E;
    /* 0x016F */ u8 unk_16F;
    /* 0x0170 */ s8 unk_170;
    /* 0x0171 */ s8 unk_171;
    /* 0x0172 */ s8 unk_172;
    /* 0x0174 */ ObjSwitchSetupActionFunc setupFunc;
    union {
        struct {
    /* 0x0178 */ ColliderJntSph colliderJntSph;
    /* 0x0198 */ ColliderJntSphElement colliderJntSphElements[1];
        };
        struct {
    /* 0x0178 */ ColliderTris colliderTris;
    /* 0x0198 */ ColliderTrisElement colliderTrisElements[2];
        };
    };
    /* 0x0250 */ f32 unk_250;
    /* 0x0254 */ f32 unk_254;
} ObjSwitch; // size = 0x258

extern const ActorInit Obj_Switch_InitVars;

#endif // Z_OBJ_SWITCH_H
