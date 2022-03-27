#ifndef Z_EN_IG_H
#define Z_EN_IG_H

#include "global.h"

struct EnIg;

typedef void (*EnIgActionFunc)(struct EnIg*, GlobalContext*);
typedef s32 (*EnIgUnkFunc)(struct EnIg*, GlobalContext*);
typedef void (*EnIgUnkFunc2)(struct EnIg*, GlobalContext*);

#define ENIG_GET_FF(thisx) ((thisx)->params & 0xFF)

typedef struct EnIg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnIgActionFunc actionFunc;
    /* 0x018C */ EnIgUnkFunc2 unk_18C;
    /* 0x0190 */ MtxF unk_190;
    /* 0x01D0 */ ColliderCylinder collider1;
    /* 0x021C */ ColliderSphere collider2;
    /* 0x0274 */ Path* unk_274;
    /* 0x0278 */ Vec3f unk_278;
    /* 0x0284 */ f32 unk_284;
    /* 0x0288 */ s32 unk_288;
    /* 0x028C */ s32 unk_28C;
    /* 0x0290 */ s32 unk_290;
    /* 0x0294 */ s32 unk_294;
    /* 0x0298 */ struct_80133038_arg2 unk_298;
    /* 0x02A4 */ s8 unk_2A4;
    /* 0x02A8 */ Actor* unk_2A8;
    /* 0x02AC */ UNK_TYPE1 unk2AC[0x4];
    /* 0x02B0 */ Vec3f unk_2B0;
    /* 0x02BC */ Vec3f unk_2BC;
    /* 0x02C8 */ UNK_TYPE1 unk2C8[0xC];
    /* 0x02D4 */ Vec3f unk_2D4;
    /* 0x02E0 */ UNK_TYPE1 unk2E0[0x6];
    /* 0x02E6 */ Vec3s unk_2E6;
    /* 0x02EC */ Vec3s jointTable[19];
    /* 0x035E */ Vec3s morphTable[19];
    /* 0x03D0 */ u16 unk_3D0;
    /* 0x03D2 */ u16 unk_3D2;
    /* 0x03D4 */ f32 unk_3D4;
    /* 0x03D8 */ UNK_TYPE1 unk3D8[0x8];
    /* 0x03E0 */ s16 unk_3E0;
    /* 0x03E2 */ s16 unk_3E2;
    /* 0x03E4 */ s16 unk_3E4;
    /* 0x03E6 */ s16 unk_3E6;
    /* 0x03E8 */ s16 unk_3E8;
    /* 0x03EA */ s16 unk_3EA;
    /* 0x03EC */ s16 unk_3EC;
    /* 0x03EE */ s16 unk_3EE;
    /* 0x03F0 */ s16 unk_3F0;
    /* 0x03F2 */ s16 unk_3F2;
    /* 0x03F4 */ s16 unk_3F4;
    /* 0x03F6 */ s16 unk_3F6;
    /* 0x03F8 */ EnIgUnkFunc unk_3F8;
    /* 0x03FC */ s32 unk_3FC;
    /* 0x0400 */ UNK_TYPE1 unk400[0x8];
    /* 0x0408 */ s32 unk_408;
} EnIg; // size = 0x40C

extern const ActorInit En_Ig_InitVars;

#endif // Z_EN_IG_H
