#ifndef Z_OBJ_VSPINYROLL_H
#define Z_OBJ_VSPINYROLL_H

#include "global.h"

struct ObjVspinyroll;

typedef void (*ObjVspinyrollActionFunc)(struct ObjVspinyroll*, GlobalContext*);

#define OBJVSPINYROLL_GET_7F(thisx) ((thisx)->params & 0x7F)
#define OBJVSPINYROLL_GET_380(thisx) (((thisx)->params >> 7) & 7)
#define OBJVSPINYROLL_GET_1C00(thisx) (((thisx)->params >> 0xA) & 7)
#define OBJVSPINYROLL_GET_4000(thisx) (((thisx)->params >> 0xE) & 1)

#define OBJVSPINYROLL_7F_7F 0x7F
#define OBJVSPINYROLL_4000_1 1

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ CollisionPoly* collisionPoly;
    /* 0x10 */ s32 bgId;
} ObjVspinyrollStruct2; // size = 0x14

typedef struct ObjVspinyroll {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ ColliderCylinder collider;
    /* 0x01A8 */ ObjVspinyrollStruct2 unk_1A8[24];
    /* 0x0388 */ ObjVspinyrollStruct2* unk_388;
    /* 0x038C */ s32 unk_38C;
    /* 0x0390 */ ObjVspinyrollActionFunc actionFunc;
    /* 0x0394 */ f32 unk_394;
    /* 0x0398 */ s32 unk_398;
    /* 0x039C */ Vec3f unk_39C[2];
    /* 0x03B4 */ Vec3f unk_3B4;
    /* 0x03C0 */ s16 unk_3C0;
    /* 0x03C2 */ s16 unk_3C2;
    /* 0x03C4 */ s16 unk_3C4;
    /* 0x03C6 */ s16 unk_3C6;
    /* 0x03C8 */ s16 unk_3C8;
} ObjVspinyroll; // size = 0x3CC

extern const ActorInit Obj_Vspinyroll_InitVars;

#endif // Z_OBJ_VSPINYROLL_H
