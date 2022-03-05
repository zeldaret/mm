#ifndef Z_EN_GG_H
#define Z_EN_GG_H

#include "global.h"

struct EnGg;
struct EnGgStruct;

typedef void (*EnGgActionFunc)(struct EnGg*, GlobalContext*);
typedef void (*EnGgUnkFunc)(struct EnGgStruct*, GlobalContext*);

typedef struct EnGgStruct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ Vec3f unk_24;
    /* 0x30 */ u8 unk_30;
    /* 0x34 */ EnGgUnkFunc unk_34;
    /* 0x38 */ EnGgUnkFunc unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ u8 unk_48;
} EnGgStruct; // size == 0x4C

typedef struct EnGg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ SkelAnime skelAnime;
    /* 0x01D4 */ EnGgActionFunc actionFunc;
    /* 0x01D8 */ Vec3s unk_1D8;
    /* 0x01DE */ Vec3s unk_1DE;
    /* 0x01E4 */ Vec3s jointTable[20];
    /* 0x025C */ Vec3s morphTable[20];
    /* 0x02D4 */ UNK_TYPE1 unk_2D4[0x6];
    /* 0x02DA */ u8 unk_2DA;
    /* 0x02DB */ u8 unk_2DB;
    /* 0x02DC */ s16 unk_2DC;
    /* 0x02DE */ UNK_TYPE1 unk2DE[4];
    /* 0x02E2 */ s16 unk_2E2;
    /* 0x02E4 */ s16 unk_2E4;
    /* 0x02E6 */ s16 unk_2E6;
    /* 0x02E8 */ s16 unk_2E8;
    /* 0x02EA */ UNK_TYPE1 unk2EA[0x1A];
    /* 0x0304 */ s16 unk_304;
    /* 0x0306 */ u8 unk_306;
    /* 0x0307 */ u8 unk_307;
    /* 0x0308 */ u8 unk_308;
    /* 0x0309 */ u8 unk_309;
    /* 0x030A */ s16 unk_30A;
    /* 0x030C */ UNK_TYPE1 unk30C[4];
    /* 0x0310 */ f32 unk_310;
    /* 0x0314 */ UNK_TYPE1 unk314[0xC];
    /* 0x0320 */ Vec3f unk_320;
    /* 0x032C */ Vec3f unk_32C;
    /* 0x0338 */ Vec3f unk_338;
    /* 0x0344 */ EnGgStruct unk_344;
} EnGg; // size = 0x390

extern const ActorInit En_Gg_InitVars;

#endif // Z_EN_GG_H
