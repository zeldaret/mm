#ifndef Z_OBJ_ICEBLOCK_H
#define Z_OBJ_ICEBLOCK_H

#include "global.h"

struct ObjIceblock;

typedef void (*ObjIceblockActionFunc)(struct ObjIceblock*, GlobalContext*);
typedef void (*ObjIceblockExtendedDrawFunc)(struct ObjIceblock*, GlobalContext*);

#define GET_ICEBLOCK_SNAP_ROT(thisx) (((thisx)->params >> 1) & 1)
#define GET_ICEBLOCK_ICEBERG(thisx) ((thisx)->params & 1)

typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
} ObjIceBlockUnkStruct; // size = 0x10

typedef struct {
    /* 0x00 */ CollisionPoly* unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
} ObjIceBlockUnkStruct2; // size = 0x10

typedef struct {
    f32 unk_00;
    f32 unk_04;
} ObjIceBlockUnkStruct3; // size = 0x8

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x14 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
} ObjIceBlockUnkStruct4; // size = 0x24

typedef struct ObjIceblock {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ ColliderCylinder collider;
    /* 0x01A8 */ ObjIceblockActionFunc actionFunc;
    /* 0x01AC */ ObjIceblockExtendedDrawFunc extendedDrawFunc;
    /* 0x01B0 */ s32 unk_1B0;
    /* 0x01B4 */ ObjIceBlockUnkStruct unk_1B4[4];
    /* 0x01F4 */ ObjIceBlockUnkStruct2 unk_1F4[5];
    /* 0x0244 */ f32 unk_244;
    /* 0x0248 */ Vec3f unk_248;
    /* 0x0254 */ Vec3s unk_254;
    /* 0x025C */ f32 unk_25C;
    /* 0x0260 */ f32 unk_260;
    /* 0x0264 */ f32* unk_264;
    /* 0x0268 */ f32 unk_268;
    /* 0x026C */ s16 unk_26C;
    /* 0x026E */ s16 unk_26E[4];
    /* 0x0276 */ s16 unk_276;
    /* 0x0278 */ s16 unk_278;
    /* 0x027C */ ObjIceBlockUnkStruct4 unk_27C;
    /* 0x02A0 */ s16 stateTimer; // re-used per-actionFunc
    /* 0x02A2 */ s16 unk_2A2;
    /* 0x02A4 */ f32 unk_2A4;
    /* 0x02A8 */ f32 unk_2A8;
    /* 0x02AC */ s16 unk_2AC;
    /* 0x02AE */ s16 meltTimer; // starts at 450 frames = 22 seconds
    /* 0x02B0 */ s8 unk_2B0;
    /* 0x02B1 */ s8 spawnCutsceneTimer;
    /* 0x02B4 */ f32 unk_2B4;
} ObjIceblock; // size = 0x2B8

extern const ActorInit Obj_Iceblock_InitVars;

#endif // Z_OBJ_ICEBLOCK_H
