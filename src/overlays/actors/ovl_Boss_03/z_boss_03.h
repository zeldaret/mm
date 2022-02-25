#ifndef Z_BOSS_03_H
#define Z_BOSS_03_H

#include "global.h"
#include "objects/object_boss03/object_boss03.h"

struct Boss03;

typedef void (*Boss03ActionFunc)(struct Boss03*, GlobalContext*);

typedef struct {
    /* 0x00 */ u8 type;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Vec3f pos;
    /* 0x10 */ Vec3f velocity;
    /* 0x1C */ Vec3f accel;
    /* 0x28 */ UNK_TYPE1 unk_28[0x4];
    /* 0x2C */ s16 unk_2C;
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ UNK_TYPE1 unk_30[0x4];
    /* 0x34 */ Vec3f unk_34;
    /* 0x40 */ UNK_TYPE1 unk_40[0x4];
} GyorgEffect; // size = 0x44

#define GYORG_EFFECT_COUNT 150

typedef struct Boss03 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ UNK_TYPE1 unk_144[0x04];
    /* 0x0148 */ SkelAnime skelAnime;
    /* 0x018C */ Vec3s jointTable[GYORG_LIMB_MAX];
    /* 0x01E6 */ Vec3s morphTable[GYORG_LIMB_MAX];
    /* 0x0240 */ s16 unk_240;
    /* 0x0242 */ u8 unk_242;
    /* 0x0243 */ UNK_TYPE1 unk_243[0x01];
    /* 0x0244 */ UNK_TYPE1 unk_244[0x08];
    /* 0x024C */ s16 unk_24C;
    /* 0x024E */ s16 unk_24E;
    /* 0x0250 */ s16 unk_250;
    /* 0x0252 */ s8 unk_252; // number of Tanron3 fish that are currently alive, maybe "numSmallFishAlive"?
    /* 0x0253 */ u8 unk_253;
    /* 0x0254 */ s16 unk_254;
    /* 0x0256 */ UNK_TYPE1 unk_256[0x02];
    /* 0x0258 */ f32 unk_258;
    /* 0x025C */ s16 unk_25C;
    /* 0x025E */ s16 unk_25E;
    /* 0x0260 */ f32 unk_260;
    /* 0x0264 */ UNK_TYPE1 unk_264[0x04];
    /* 0x0268 */ Vec3f unk_268;
    /* 0x0274 */ s16 unk_274;
    /* 0x0276 */ s16 unk_276;
    /* 0x0278 */ f32 unk_278;
    /* 0x027C */ f32 unk_27C;
    /* 0x0280 */ UNK_TYPE1 unk_280[0x1C];
    /* 0x029C */ s16 unk_29C;
    /* 0x029E */ s16 unk_29E;
    /* 0x02A0 */ s16 unk_2A0;
    /* 0x02A2 */ Vec3s unk_2A2;
    /* 0x02A8 */ s16 unk_2A8;
    /* 0x02AA */ UNK_TYPE1 unk_2AA[0x02];
    /* 0x02AC */ Vec3f unk_2AC;
    /* 0x02B8 */ f32 unk_2B8;
    /* 0x02BC */ s8 unk_2BC;
    /* 0x02BD */ s8 unk_2BD;
    /* 0x02BE */ UNK_TYPE1 unk_2BE[0x02];
    /* 0x02C0 */ UNK_TYPE1 unk_2C0[0x04];
    /* 0x02C0 */ f32 unk_2C4;
    /* 0x02C8 */ UNK_TYPE1 unk_2C8[0x0C];
    /* 0x02D4 */ UNK_TYPE1 unk_2D4[0x01];
    /* 0x02D5 */ u8 unk_2D5;
    /* 0x02D6 */ UNK_TYPE1 unk_2D6[0x02];
    /* 0x02D8 */ UNK_TYPE1 unk_2D8[0x04];
    /* 0x02DC */ Vec3f unk_2DC[UNK_SIZE];
    /* 0x02E8 */ UNK_TYPE1 unk_2E8[0x3C];
    /* 0x0324 */ s16 unk_324;
    /* 0x0326 */ UNK_TYPE1 unk_326[0x2];
    /* 0x0328 */ Boss03ActionFunc actionFunc;
    /* 0x032C */ ColliderJntSph collider1;
    /* 0x034C */ ColliderJntSphElement unk_34C[2];
    /* 0x03CC */ ColliderJntSph collider2;
    /* 0x03EC */ ColliderJntSphElement unk_3EC[5];
    /* 0x052C */ f32 unk_52C;
    /* 0x0530 */ s32 unk_530;
    /* 0x0534 */ s16 unk_534;
    /* 0x0536 */ UNK_TYPE1 unk_536[0x02];
    /* 0x0538 */ UNK_TYPE1 unk_538[0x44];
} Boss03; // size = 0x57C

extern const ActorInit Boss_03_InitVars;

#endif // Z_BOSS_03_H
