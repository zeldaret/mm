#ifndef Z_OBJ_TOKEI_STEP_H
#define Z_OBJ_TOKEI_STEP_H

#include <global.h>

struct ObjTokeiStep;

typedef void (*ObjTokeiStepFunc)(struct ObjTokeiStep*, struct GlobalContext*);

typedef struct ObjTokeiStepStep {
    /* 0x00 */ Vec3f unk0;
    /* 0x0C */ f32 unkc;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s8 unk12;
    /* 0x13 */ s8 unk13;
} ObjTokeiStepStep; // size = 0x14

typedef struct ObjTokeiStep {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15c */ ObjTokeiStepFunc actionFunc;
    /* 0x160 */ ObjTokeiStepStep steps[7];
} ObjTokeiStep; // size = 0x1EC

extern const ActorInit Obj_Tokei_Step_InitVars;

#endif // Z_OBJ_TOKEI_STEP_H
