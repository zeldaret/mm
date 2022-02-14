#ifndef Z_OBJ_SKATEBLOCK_H
#define Z_OBJ_SKATEBLOCK_H

#include "global.h"

struct ObjSkateblock;

typedef void (*ObjSkateblockActionFunc)(struct ObjSkateblock*, GlobalContext*);

#define OBJSKAEBLOCK_GET_F(thisx) ((thisx)->params & 0xF)

typedef struct {
    /* 0x00 */ CollisionPoly* poly;
    /* 0x04 */ f32 height;
    /* 0x08 */ s32 bgId;
} ObjSkateblockFloor; // size = 0xC

typedef struct ObjSkateblock {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ ObjSkateblockActionFunc actionFunc;
    /* 0x0160 */ f32 unk_160;
    /* 0x0164 */ f32 unk_164;
    /* 0x0168 */ f32 unk_168;
    /* 0x016C */ f32* unk_16C;
    /* 0x0170 */ s16 unk_170;
    /* 0x0172 */ s16 unk_172[4];
    /* 0x017A */ s16 unk_17A;
    /* 0x017C */ s16 unk_17C;
    /* 0x0180 */ f32 unk_180;
    /* 0x0184 */ ObjSkateblockFloor unk_184[5];
    /* 0x01C0 */ u8 unk_1C0;
    /* 0x01C1 */ u8 unk_1C1;
} ObjSkateblock; // size = 0x1C4

extern const ActorInit Obj_Skateblock_InitVars;

#endif // Z_OBJ_SKATEBLOCK_H
