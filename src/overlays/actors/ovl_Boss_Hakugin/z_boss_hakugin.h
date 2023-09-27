#ifndef Z_BOSS_HAKUGIN_H
#define Z_BOSS_HAKUGIN_H

#include "global.h"

struct BossHakugin;

typedef void (*BossHakuginActionFunc)(struct BossHakugin*, PlayState*);

typedef struct BossHakuginEffect {
    /* 0x00 */ Vec3f unk_0;
    /* 0x0C */ Vec3f unk_C;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ Vec3s unk_1C;
    /* 0x24 */ f32 unk_24;
} BossHakuginEffect; // size = 0x28

#define BOSS_HAKUGIN_EFFECT_COUNT 180

typedef struct BossHakuginUnkStruct_2618 {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ ColliderTris unk_14;
    /* 0x34 */ ColliderTrisElement unk_34;
} BossHakuginUnkStruct_2618; // size = 0x90

typedef struct BossHakuginFhgFlashUnkStruct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ char unk_0C[0x8];
} BossHakuginFhgFlashUnkStruct; // size = 0x14

typedef struct BossHakugin {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ BossHakuginActionFunc actionFunc;
    /* 0x018C */ char unk_018C[0x1];
    /* 0x018D */ s8 unk_018D;
    /* 0x018E */ char unk_018E[3];
    /* 0x0191 */ u8 unk_0191;
    /* 0x0192 */ char unk_0192[0x1];
    /* 0x0193 */ u8 unk_0193;
    /* 0x0194 */ char unk_0194[0x8];
    /* 0x019C */ s16 unk_019C;
    /* 0x019E */ s16 unk_019E;
    /* 0x01A0 */ s16 unk_01A0;
    /* 0x01A2 */ s16 unk_01A2;
    /* 0x01A4 */ s16 unk_01A4;
    /* 0x01A6 */ s16 unk_01A6;
    /* 0x01A8 */ char unk_01A8[4];
    /* 0x01AC */ s16 unk_01AC;
    /* 0x01AE */ char unk_01AE[0x2];
    /* 0x01B0 */ u32 unk_01B0;
    /* 0x01B4 */ s32 unk_01B4;
    /* 0x01B8 */ char unk_01B8[0xC];
    /* 0x01C4 */ f32 unk_01C4;
    /* 0x01C8 */ f32 unk_01C8;
    /* 0x01CC */ char unk_01CC[0x8];
    /* 0x01D4 */ f32 unk_01D4;
    /* 0x01D8 */ char unk_01D8[0x10];
    /* 0x01E8 */ Vec3s jointTable[33];
    /* 0x02AE */ Vec3s morphTable[33];
    /* 0x0374 */ char unk_0374[0x6];
    /* 0x037A */ Vec3s unk_037A;
    /* 0x0380 */ char unk_0380[0xC];
    /* 0x038C */ Vec3f unk_038C;
    /* 0x0398 */ Vec3f bodyPartsPos[15];
    /* 0x044C */ char unk_044C[0xC];
    /* 0x0458 */ Vec3f unk_0458;
    /* 0x0464 */ Vec3f unk_0464;
    /* 0x0470 */ LightNode* lightNode;
    /* 0x0474 */ LightInfo lightInfo;
    /* 0x0482 */ char unk_0482[0x2];
    /* 0x0484 */ ColliderJntSph unk_0484;
    /* 0x04A4 */ ColliderJntSphElement unk_04A4[19];
    /* 0x0964 */ ColliderCylinder unk_0964;
    /* 0x09B0 */ Actor* unk_09B0[8];
    /* 0x09D0 */ Actor* unk_09D0[10];
    /* 0x09F8 */ BossHakuginEffect unk_09F8[BOSS_HAKUGIN_EFFECT_COUNT];
    /* 0x2618 */ BossHakuginUnkStruct_2618 unk_2618[20];
    /* 0x3158 */ BossHakuginFhgFlashUnkStruct unk_3158[5][15];
    /* 0x3734 */ char unk_3734[0x84];
    /* 0x37B8 */ ColliderSphere unk_37B8;
} BossHakugin; // size = 0x3810

#endif // Z_BOSS_HAKUGIN_H
