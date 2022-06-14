#ifndef Z_EN_GO_H
#define Z_EN_GO_H

#include "global.h"

struct EnGo;

typedef void (*EnGoActionFunc)(struct EnGo*, GlobalContext*);

#define ENGO_GET_F(thisx) (((thisx)->params & 0xF) & 0xFF)
#define ENGO_GET_70(thisx) ((((thisx)->params & 0x70) >> 4) & 0xFF)
#define ENGO_GET_7F80(thisx) ((((thisx)->params & 0x7F80) >> 7) & 0xFF)

enum {
    /* 0 */ ENGO_F_0,
    /* 1 */ ENGO_F_1,
    /* 2 */ ENGO_F_2,
    /* 3 */ ENGO_F_3,
    /* 4 */ ENGO_F_4,
    /* 5 */ ENGO_F_5,
    /* 6 */ ENGO_F_6,
    /* 7 */ ENGO_F_7,
    /* 8 */ ENGO_F_8,
};

enum {
    /* 0 */ ENGO_70_0,
    /* 1 */ ENGO_70_1,
    /* 2 */ ENGO_70_2,
    /* 3 */ ENGO_70_3,
    /* 4 */ ENGO_70_4,
    /* 5 */ ENGO_70_5,
};

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x04 */ Vec3s unk_04;
    /* 0x0A */ Vec3s unk_0A;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ Vec3f unk_1C;
    /* 0x28 */ Vec3f unk_28;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
} EnGoStruct; // size = 0x3C;

typedef struct EnGo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnGoActionFunc actionFunc;
    /* 0x018C */ EnGoActionFunc unk_18C;
    /* 0x0190 */ EnGoActionFunc unk_190;
    /* 0x0194 */ ColliderCylinder colliderCylinder;
    /* 0x01E0 */ UNK_TYPE1 unk1E0[0x4C];
    /* 0x022C */ ColliderSphere colliderSphere;
    /* 0x0284 */ Path* unk_284;
    /* 0x0288 */ s8 unk_288;
    /* 0x0289 */ s8 unk_289;
    /* 0x028C */ s32 unk_28C;
    /* 0x0290 */ Vec3f unk_290;
    /* 0x029C */ Vec3f unk_29C;
    /* 0x02A8 */ Vec3s unk_2A8;
    /* 0x02AE */ Vec3s unk_2AE;
    /* 0x02B4 */ Vec3s jointTable[18];
    /* 0x0320 */ Vec3s morphTable[18];
    /* 0x038C */ Actor* unk_38C;
    /* 0x0390 */ u16 unk_390;
    /* 0x0392 */ u16 unk_392;
    /* 0x0394 */ u8 unk_394;
    /* 0x0398 */ f32 unk_398;
    /* 0x039C */ f32 unk_39C;
    /* 0x03A0 */ f32 unk_3A0;
    /* 0x03A4 */ f32 unk_3A4;
    /* 0x03A8 */ f32 unk_3A8;
    /* 0x03AC */ UNK_TYPE1 unk3AC[0x2];
    /* 0x03AE */ s16 unk_3AE;
    /* 0x03B0 */ s16 unk_3B0;
    /* 0x03B2 */ s16 unk_3B2;
    /* 0x03B4 */ s16 unk_3B4;
    /* 0x03B6 */ s16 unk_3B6;
    /* 0x03B8 */ s16 unk_3B8;
    /* 0x03BA */ s16 unk_3BA;
    /* 0x03BC */ s16 unk_3BC;
    /* 0x03BE */ s16 unk_3BE;
    /* 0x03C0 */ s16 unk_3C0;
    /* 0x03C2 */ s16 unk_3C2;
    /* 0x03C4 */ s16 unk_3C4;
    /* 0x03C6 */ s16 unk_3C6;
    /* 0x03C8 */ s16 unk_3C8[3];
    /* 0x03CE */ s16 unk_3CE[3];
    /* 0x03D4 */ s16 unk_3D4;
    /* 0x03D8 */ void* unk_3D8;
    /* 0x03DC */ s32 unk_3DC;
    /* 0x03E0 */ UNK_TYPE1 unk3E0[0x4];
    /* 0x03E4 */ s32 unk_3E4;
    /* 0x03E8 */ s32 unk_3E8;
    /* 0x03EC */ s32 unk_3EC;
    /* 0x03F0 */ s32 unk_3F0;
    /* 0x03F4 */ s32 unk_3F4;
    /* 0x03F8 */ EnGoStruct unk_3F8[32];
} EnGo; // size = 0xB78

extern const ActorInit En_Go_InitVars;

#endif // Z_EN_GO_H
