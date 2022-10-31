#ifndef Z_EN_KAIZOKU_H
#define Z_EN_KAIZOKU_H

#include "global.h"
#include "objects/object_kz/object_kz.h"

struct EnKaizoku;

typedef void (*EnKaizokuActionFunc)(struct EnKaizoku*, PlayState*);
typedef s32 (*EnKaizokuUnkFunc)(PlayState*, Actor*);

typedef struct EnKaizoku {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnKaizokuUnkFunc unk_144;
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ Vec3s jointTable[KAIZOKU_LIMB_MAX];
    /* 0x21C */ Vec3s morphTable[KAIZOKU_LIMB_MAX];
    /* 0x2AC */ EnKaizokuActionFunc actionFunc;
    /* 0x2B0 */ s16 unk_2B0;
    /* 0x2B2 */ s16 unk_2B2;
    /* 0x2B4 */ s16 unk_2B4;
    /* 0x2B6 */ s16 unk_2B6;
    /* 0x2B8 */ s16 unk_2B8;
    /* 0x2BA */ s16 unk_2BA;
    /* 0x2BC */ s16 unk_2BC;
    /* 0x2BE */ s16 unk_2BE;
    /* 0x2C0 */ f32 unk_2C0;
    /* 0x2C4 */ f32 unk_2C4;
    /* 0x2C8 */ s16 unk_2C8;
    /* 0x2CA */ s16 unk_2CA;
    /* 0x2CC */ s16 unk_2CC;
    /* 0x2CE */ s16 unk_2CE;
    /* 0x2D0 */ s16 unk_2D0;
    /* 0x2D2 */ s16 unk_2D2;
    /* 0x2D4 */ s16 unk_2D4;
    /* 0x2D6 */ s16 unk_2D6;
    /* 0x2D8 */ u8 unk_2D8;
    /* 0x2D9 */ u8 unk_2D9;
    /* 0x2DC */ f32 unk_2DC;
    /* 0x2E0 */ f32 unk_2E0;
    /* 0x2E4 */ s32 unk_2E4;
    /* 0x2E8 */ s32 unk_2E8;
    /* 0x2EC */ s32 unk_2EC;
    /* 0x2F0 */ f32 unk_2F0;
    /* 0x2F4 */ s16 unk_2F4;
    /* 0x2F8 */ Vec3f unk_2F8;
    /* 0x304 */ Vec3f unk_304;
    /* 0x310 */ Vec3f unk_310[15];
    /* 0x3C4 */ Vec3f unk_3C4;
    /* 0x3D0 */ s32 unk_3D0;
    /* 0x3D4 */ ColliderCylinder unk_3D4;
    /* 0x420 */ ColliderQuad unk_420;
    /* 0x4A0 */ UNK_TYPE1 pad_4A0[0xD8];
    /* 0x578 */ s16 unk_578;
    /* 0x57A */ s16 unk_57A;
    /* 0x57C */ s16 unk_57C;
    /* 0x580 */ Vec3f unk_580;
    /* 0x58C */ Vec3f unk_58C;
    /* 0x598 */ s32 unk_598;
    /* 0x59C */ s16 unk_59C;
    /* 0x59E */ s16 unk_59E; // Cam ID
    /* 0x5A0 */ s16 unk_5A0;
    /* 0x5A2 */ s16 unk_5A2;
    /* 0x5A4 */ Vec3f unk_5A4; // cam eye
    /* 0x5B0 */ Vec3f unk_5B0; // cam at
    /* 0x5BC */ Vec3f unk_5BC; // cam up
    /* 0x5C8 */ Vec3f unk_5C8;
    /* 0x5D4 */ Vec3f unk_5D4;
    /* 0x5E0 */ f32 unk_5E0;
    /* 0x5E4 */ f32 unk_5E4;
    /* 0x5E8 */ f32 unk_5E8;
    /* 0x5EC */ f32 unk_5EC;
} EnKaizoku; // size = 0x5F0

#endif // Z_EN_KAIZOKU_H
