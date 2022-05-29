#ifndef Z_OBJ_OSHIHIKI_H
#define Z_OBJ_OSHIHIKI_H

#include "global.h"

struct ObjOshihiki;

typedef void (*ObjOshihikiActionFunc)(struct ObjOshihiki*, GlobalContext*);

#define OBJOSHIHIKI_GET_F(thisx) ((thisx)->params & 0xF)
#define OBJOSHIHIKI_GET_F0(thisx) (((thisx)->params >> 4) & 0xF)
#define OBJOSHIHIKI_GET_7F00(thisx) (((thisx)->params >> 8) & 0x7F)
#define OBJOSHIHIKI_GET_FF00(thisx) (((thisx)->params >> 8) & 0xFF)

enum {
    /* 0 */ OBJOSHIHIKI_F_0,
    /* 1 */ OBJOSHIHIKI_F_1,
    /* 2 */ OBJOSHIHIKI_F_2,
    /* 3 */ OBJOSHIHIKI_F_3,
    /* 4 */ OBJOSHIHIKI_F_4,
    /* 5 */ OBJOSHIHIKI_F_5,
    /* 6 */ OBJOSHIHIKI_F_6,
    /* 7 */ OBJOSHIHIKI_F_7,
    /* 8 */ OBJOSHIHIKI_F_8,
};

#define OBJOSHIHIKI_FF00_0 0
#define OBJOSHIHIKI_FF00_80 0x80

#define PUSHBLOCK_ON_SCENE       (1 << 0)
#define PUSHBLOCK_SETUP_ON_SCENE (1 << 1)
#define PUSHBLOCK_ON_ACTOR       (1 << 2)
#define PUSHBLOCK_SETUP_ON_ACTOR (1 << 3)
#define PUSHBLOCK_PUSH           (1 << 4)
#define PUSHBLOCK_SETUP_PUSH     (1 << 5)
#define PUSHBLOCK_FALL           (1 << 6)
#define PUSHBLOCK_SETUP_FALL     (1 << 7)
#define PUSHBLOCK_MOVE_UNDER     (1 << 8)

typedef struct ObjOshihiki {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ ObjOshihikiActionFunc actionFunc;
    /* 0x0160 */ u16 stateFlags;
    /* 0x0162 */ s16 timer;
    /* 0x0164 */ f32 yawSin;
    /* 0x0168 */ f32 yawCos;
    /* 0x016C */ f32 pushSpeed;
    /* 0x0170 */ f32 pushDist;
    /* 0x0174 */ f32 direction;
    /* 0x0178 */ s32 floorBgIds[5];
    /* 0x018C */ CollisionPoly* floorPolys[5];
    /* 0x01A0 */ f32 floorHeights[5];
    /* 0x01B4 */ s16 highestFloor;
    /* 0x01B6 */ u8 cantMove;
    /* 0x01B8 */ struct ObjOshihiki* blockUnder;
    /* 0x01BC */ f32 underDistX;
    /* 0x01C0 */ f32 underDistZ;
    /* 0x01C4 */ s8 textureStep;
    /* 0x01C5 */ Color_RGB8 color;
    /* 0x01C8 */ AnimatedMaterial* texture;
} ObjOshihiki; // size = 0x1CC

extern const ActorInit Obj_Oshihiki_InitVars;

#endif // Z_OBJ_OSHIHIKI_H
