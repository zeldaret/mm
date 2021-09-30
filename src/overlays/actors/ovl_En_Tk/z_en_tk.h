#ifndef Z_EN_TK_H
#define Z_EN_TK_H

#include "global.h"

struct EnTk;

typedef void (*EnTkActionFunc)(struct EnTk*, GlobalContext*);
typedef void (*EnTkUnkFunc)(struct EnTk*, GlobalContext*);

#define ENTK_GET_F(thisx) ((thisx)->params & 0xF)
#define ENTK_GET_7F0(thisx) (((thisx)->params >> 4) & 0x7F)
#define ENTK_GET_F800(thisx) ((((thisx)->params >> 0xB) & 0x1F) & 0xFF)

typedef struct EnTk {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnTkActionFunc actionFunc;
    /* 0x018C */ ColliderCylinder collider;
    /* 0x01D8 */ Vec3s jointTable[18];
    /* 0x0244 */ Vec3s morphTable[18];
    /* 0x02B0 */ s8 unk_2B0;
    /* 0x02B1 */ s8 unk_2B1;
    /* 0x02B4 */ Vec3f unk_2B4;
    /* 0x02C0 */ s16 unk_2C0;
    /* 0x02C2 */ s16 unk_2C2;
    /* 0x02C4 */ s16 unk_2C4;
    /* 0x02C6 */ s16 unk_2C6;
    /* 0x02C8 */ UNK_TYPE1 unk2C8[0x2];
    /* 0x02CA */ u16 unk_2CA;
    /* 0x02CC */ s16 unk_2CC;
    /* 0x02D0 */ s32 unk_2D0;
    /* 0x02D4 */ s32 unk_2D4;
    /* 0x02D8 */ f32 unk_2D8;
    /* 0x02DC */ f32 unk_2DC;
    /* 0x02E0 */ s32 unk_2E0;
    /* 0x02E4 */ s16 unk_2E4;
    /* 0x02E6 */ u16 unk_2E6;
    /* 0x02E8 */ s16 unk_2E8;
    /* 0x02EC */ Vec3f unk_2EC;
    /* 0x02F8 */ Vec3s unk_2F8;
    /* 0x0300 */ Vec3f unk_300;
    /* 0x030C */ EnTkUnkFunc unk_30C;
    /* 0x0310 */ s16 unk_310;
    /* 0x0312 */ s16 cutscenes[2];
    /* 0x0316 */ s16 unk_316;
    /* 0x0318 */ s16 unk_318;
    /* 0x031A */ s16 unk_31A;
    /* 0x031C */ s16 unk_31C;
    /* 0x0320 */ f32 unk_320;
    /* 0x0324 */ Vec3f unk_324[6];
    /* 0x036C */ s32 unk_36C;
    /* 0x0370 */ UNK_TYPE1 unk370[0x58];
    /* 0x03C8 */ Path* unk_3C8;
    /* 0x03CC */ u8 unk_3CC;
    /* 0x03CE */ u16 unk_3CE;
    /* 0x03D0 */ s32 unk_3D0;
    /* 0x03D4 */ Vec3f unk_3D4;
    /* 0x03E0 */ s32 unk_3E0;
    /* 0x03E4 */ s32 unk_3E4;
    /* 0x03E8 */ s32 unk_3E8;
    /* 0x03EC */ s32 unk_3EC;
    /* 0x03F0 */ s32 unk_3F0;
} EnTk; // size = 0x3F4

extern const ActorInit En_Tk_InitVars;

#endif // Z_EN_TK_H
