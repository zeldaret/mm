#ifndef Z_OBJ_SPINYROLL_H
#define Z_OBJ_SPINYROLL_H

#include "global.h"

struct ObjSpinyroll;

typedef void (*ObjSpinyrollActionFunc)(struct ObjSpinyroll*, PlayState*);
typedef s32 (*ObjSpinyrollColFunc)(CollisionContext*, f32*, CollisionPoly**, s32*, Vec3f*, struct ObjSpinyroll*);

#define OBJSPINYROLL_GET_7F(thisx) ((thisx)->params & 0x7F)
#define OBJSPINYROLL_GET_380(thisx) (((thisx)->params >> 7) & 7)
#define OBJSPINYROLL_GET_1C00(thisx) (((thisx)->params >> 0xA) & 7)
#define OBJSPINYROLL_GET_C000(thisx) (((thisx)->params >> 0xE) & 3)

#define OBJSPINYROLL_GET_7F_7F 0x7F
#define OBJSPINYROLL_GET_C000_0 0
#define OBJSPINYROLL_GET_C000_1 1

typedef struct {
    /* 0x0 */ f32 unk_00;
    /* 0x4 */ CollisionPoly* unk_04;
    /* 0x8 */ s32 bgId;
} ObjSpinyrollSubStruct; // size = 0xC

typedef struct {
    /* 0x00 */ ObjSpinyrollSubStruct unk_00[10];
} ObjSpinyrollStruct; // size = 0x78

typedef struct {
    /* 0x00 */ ObjSpinyrollStruct unk_00[2];
    /* 0xF0 */ ObjSpinyrollStruct* unk_F0;
    /* 0xF4 */ s32 unk_F4;
} ObjSpinyrollStruct2; // size = 0xF8?

typedef struct ObjSpinyroll {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ColliderTris collider;
    /* 0x17C */ ColliderTrisElement colliderElements[6];
    /* 0x3A4 */ ObjSpinyrollStruct2 unk_3A4;
    ///* 0x494 */ ObjSpinyrollStruct* unk_494; // alternative testing
    ///* 0x498 */ s32 unk_498;
    /* 0x49C */ s32 unk_49C;
    /* 0x4A0 */ ObjSpinyrollActionFunc actionFunc;
    /* 0x4A4 */ f32 unk_4A4;
    /* 0x4A8 */ s32 unk_4A8;
    /* 0x4AC */ Vec3f unk_4AC[2];
    /* 0x4C4 */ Vec3f unk_4C4;
    /* 0x4D0 */ f32 unk_4D0;
    /* 0x4D4 */ f32 unk_4D4;
    /* 0x4D8 */ s16 unk_4D8;
    /* 0x4DA */ s16 unk_4DA;
    /* 0x4DC */ s16 unk_4DC;
    /* 0x4DE */ s16 unk_4DE;
    /* 0x4E0 */ s16 unk_4E0;
    /* 0x4E2 */ s16 unk_4E2;
} ObjSpinyroll; // size = 0x4E4

extern const ActorInit Obj_Spinyroll_InitVars;

#endif // Z_OBJ_SPINYROLL_H
