#ifndef Z_OBJ_SPINYROLL_H
#define Z_OBJ_SPINYROLL_H

#include "global.h"

struct ObjSpinyroll;

typedef void (*ObjSpinyrollActionFunc)(struct ObjSpinyroll*, GlobalContext*);
typedef s32 (*ObjSpinyrollColFunc)(CollisionContext*, f32*, CollisionPoly**, s32*, Vec3f*, struct ObjSpinyroll*);

#define OBJSPINYROLL_GET_7F(thisx) ((thisx)->params & 0x7F)
#define OBJSPINYROLL_GET_380(thisx) (((thisx)->params >> 7) & 7)
#define OBJSPINYROLL_GET_1C00(thisx) (((thisx)->params >> 0xA) & 7)
#define OBJSPINYROLL_GET_C000(thisx) (((thisx)->params >> 0xE) & 3)

#define OBJSPINYROLL_GET_7F_7F 0x7F
#define OBJSPINYROLL_GET_C000_0 0
#define OBJSPINYROLL_GET_C000_1 1

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ CollisionPoly* unk_04;
    /* 0x08 */ s32 bgId;
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
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ ColliderTris collider;
    /* 0x017C */ ColliderTrisElement colliderElements[6];
    /* 0x03A4 */ ObjSpinyrollStruct2 unk_3A4;
    ///* 0x0494 */ ObjSpinyrollStruct* unk_494; // alternative testing
    ///* 0x0498 */ s32 unk_498;
    /* 0x049C */ s32 unk_49C;
    /* 0x04A0 */ ObjSpinyrollActionFunc actionFunc;
    /* 0x04A4 */ f32 unk_4A4;
    /* 0x04A8 */ s32 unk_4A8;
    /* 0x04AC */ Vec3f unk_4AC[2];
    /* 0x04C4 */ Vec3f unk_4C4;
    /* 0x04D0 */ f32 unk_4D0;
    /* 0x04D4 */ f32 unk_4D4;
    /* 0x04D8 */ s16 unk_4D8;
    /* 0x04DA */ s16 unk_4DA;
    /* 0x04DC */ s16 unk_4DC;
    /* 0x04DE */ s16 unk_4DE;
    /* 0x04E0 */ s16 unk_4E0;
    /* 0x04E2 */ s16 unk_4E2;
} ObjSpinyroll; // size = 0x4E4

extern const ActorInit Obj_Spinyroll_InitVars;

#endif // Z_OBJ_SPINYROLL_H
