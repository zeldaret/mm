#ifndef Z_BOSS_03_H
#define Z_BOSS_03_H

#include "global.h"
#include "objects/object_boss03/object_boss03.h"

struct Boss03;

typedef void (*Boss03ActionFunc)(struct Boss03*, GlobalContext*);

typedef struct Boss03 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ UNK_TYPE1 unk_144[0x04];
    /* 0x0148 */ SkelAnime skelAnime;
    /* 0x018C */ Vec3s jointTable[GYORG_LIMB_MAX];
    /* 0x01E6 */ Vec3s morphTable[GYORG_LIMB_MAX];
    /* 0x0240 */ s16 unk_240;
    /* 0x0242 */ UNK_TYPE1 unk_242[0x02];
    /* 0x0244 */ UNK_TYPE1 unk_244[0x0C];
    /* 0x0250 */ UNK_TYPE1 unk_250[0x02];
    /* 0x0252 */ s8 unk_252; // number of Tanron3 fish that are currently alive, maybe "numSmallFishAlive"?
    /* 0x0253 */ UNK_TYPE1 unk_253[0x01];
    /* 0x0254 */ UNK_TYPE1 unk_254[0x01];
    /* 0x0258 */ f32 unk_258;
    /* 0x025C */ UNK_TYPE1 unk_25C[0x02];
    /* 0x025E */ s16 unk_25E;
    /* 0x0260 */ f32 unk_260;
    /* 0x0260 */ UNK_TYPE1 unk_264[0x58];
    /* 0x02BC */ s8 unk_2BC;
    /* 0x02BD */ UNK_TYPE1 unk_2BD[0x03];
    /* 0x02C0 */ UNK_TYPE1 unk_2C0[0x14];
    /* 0x02D4 */ UNK_TYPE1 unk_2D4[0x01];
    /* 0x02D5 */ u8 unk_2D5;
    /* 0x02D6 */ UNK_TYPE1 unk_2D6[0x02];
    /* 0x02D8 */ UNK_TYPE1 unk_2D8[0x4C];
    /* 0x0324 */ s16 unk_324;
    /* 0x0326 */ UNK_TYPE1 unk_326[0x2];
    /* 0x0328 */ Boss03ActionFunc actionFunc;
    /* 0x032C */ ColliderJntSph collider1;
    /* 0x034C */ ColliderJntSphElement unk_34C[2];
    /* 0x03CC */ ColliderJntSph collider2;
    /* 0x03EC */ ColliderJntSphElement unk_3EC[5];
    /* 0x052C */ UNK_TYPE1 unk_52C[0x50];
} Boss03; // size = 0x57C

extern const ActorInit Boss_03_InitVars;

#endif // Z_BOSS_03_H
