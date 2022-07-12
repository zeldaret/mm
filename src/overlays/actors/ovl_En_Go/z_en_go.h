#ifndef Z_EN_GO_H
#define Z_EN_GO_H

#include "global.h"

struct EnGo;

typedef void (*EnGoActionFunc)(struct EnGo*, PlayState*);

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
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnGoActionFunc actionFunc;
    /* 0x18C */ EnGoActionFunc unk_18C;
    /* 0x190 */ EnGoActionFunc unk_190;
    /* 0x194 */ ColliderCylinder colliderCylinder;
    /* 0x1E0 */ UNK_TYPE1 unk1E0[0x4C];
    /* 0x22C */ ColliderSphere colliderSphere;
    /* 0x284 */ Path* unk_284;
    /* 0x288 */ s8 unk_288;
    /* 0x289 */ s8 unk_289;
    /* 0x28C */ s32 unk_28C;
    /* 0x290 */ Vec3f unk_290;
    /* 0x29C */ Vec3f unk_29C;
    /* 0x2A8 */ Vec3s unk_2A8;
    /* 0x2AE */ Vec3s unk_2AE;
    /* 0x2B4 */ Vec3s jointTable[18];
    /* 0x320 */ Vec3s morphTable[18];
    /* 0x38C */ Actor* unk_38C;
    /* 0x390 */ u16 unk_390;
    /* 0x392 */ u16 unk_392;
    /* 0x394 */ u8 unk_394;
    /* 0x398 */ f32 unk_398;
    /* 0x39C */ f32 unk_39C;
    /* 0x3A0 */ f32 unk_3A0;
    /* 0x3A4 */ f32 unk_3A4;
    /* 0x3A8 */ f32 unk_3A8;
    /* 0x3AC */ UNK_TYPE1 unk3AC[0x2];
    /* 0x3AE */ s16 unk_3AE;
    /* 0x3B0 */ s16 unk_3B0;
    /* 0x3B2 */ s16 unk_3B2;
    /* 0x3B4 */ s16 unk_3B4;
    /* 0x3B6 */ s16 unk_3B6;
    /* 0x3B8 */ s16 unk_3B8;
    /* 0x3BA */ s16 unk_3BA;
    /* 0x3BC */ s16 unk_3BC;
    /* 0x3BE */ s16 unk_3BE;
    /* 0x3C0 */ s16 unk_3C0;
    /* 0x3C2 */ s16 unk_3C2;
    /* 0x3C4 */ s16 unk_3C4;
    /* 0x3C6 */ s16 unk_3C6;
    /* 0x3C8 */ s16 unk_3C8[3];
    /* 0x3CE */ s16 unk_3CE[3];
    /* 0x3D4 */ s16 unk_3D4;
    /* 0x3D8 */ void* unk_3D8;
    /* 0x3DC */ s32 unk_3DC;
    /* 0x3E0 */ UNK_TYPE1 unk3E0[0x4];
    /* 0x3E4 */ s32 unk_3E4;
    /* 0x3E8 */ s32 unk_3E8;
    /* 0x3EC */ s32 unk_3EC;
    /* 0x3F0 */ s32 unk_3F0;
    /* 0x3F4 */ s32 unk_3F4;
    /* 0x3F8 */ EnGoStruct unk_3F8[32];
} EnGo; // size = 0xB78

extern const ActorInit En_Go_InitVars;

#endif // Z_EN_GO_H
