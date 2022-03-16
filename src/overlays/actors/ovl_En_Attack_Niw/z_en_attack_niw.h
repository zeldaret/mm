#ifndef Z_EN_ATTACK_NIW_H
#define Z_EN_ATTACK_NIW_H

#include "global.h"
#include "objects/object_niw/object_niw.h"

struct EnAttackNiw;

typedef void (*EnAttackNiwActionFunc)(struct EnAttackNiw*, GlobalContext*);

typedef struct EnAttackNiw {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[OBJECT_NIW_LIMB_MAX];
    /* 0x1E8 */ Vec3s morphTable[OBJECT_NIW_LIMB_MAX];
    /* 0x248 */ EnAttackNiwActionFunc actionFunc;
    /* 0x24C */ s16 unk_24C;
    /* 0x24E */ s16 unk_24E;
    /* 0x250 */ s16 unk_250;
    /* 0x252 */ s16 unk_252;
    /* 0x254 */ s16 unk_254;
    /* 0x256 */ s16 unk_256;
    /* 0x258 */ s16 unk_258;
    /* 0x25A */ s16 unk_25A;
    /* 0x25C */ f32 unk_25C;
    /* 0x260 */ f32 unk_260;
    /* 0x264 */ f32 unk_264;
    /* 0x268 */ UNK_TYPE1 unk268[8];
    /* 0x270 */ f32 unk_270;
    /* 0x274 */ f32 unk_274;
    /* 0x278 */ f32 unk_278;
    /* 0x27C */ f32 unk_27C;
    /* 0x280 */ f32 unk_280;
    /* 0x284 */ s16 unk_284;
    /* 0x286 */ s16 unk_286;
    /* 0x288 */ UNK_TYPE1 unk288[2];
    /* 0x28A */ s16 unk_28A;
    /* 0x28C */ UNK_TYPE1 unk28C[4];
    /* 0x290 */ Vec3f unk_290;
    /* 0x29C */ f32 unk_29C;
    /* 0x2A0 */ f32 unk_2A0;
    /* 0x2A4 */ f32 unk_2A4;
    /* 0x2A8 */ f32 unk_2A8;
    /* 0x2AC */ f32 unk_2AC;
    /* 0x2B0 */ f32 unk_2B0;
    /* 0x2B4 */ f32 unk_2B4;
    /* 0x2B8 */ f32 unk_2B8;
    /* 0x2BC */ UNK_TYPE1 unk2BC[0xC];
    /* 0x2C8 */ f32 unk_2C8;
    /* 0x2CC */ f32 unk_2CC;
    /* 0x2D0 */ UNK_TYPE1 unk2D0[4];
    /* 0x2D4 */ f32 unk_2D4;
    /* 0x2D8 */ f32 unk_2D8;
    /* 0x2DC */ f32 unk_2DC;
} EnAttackNiw; // size = 0x2E0

extern const ActorInit En_Attack_Niw_InitVars;

#endif // Z_EN_ATTACK_NIW_H
