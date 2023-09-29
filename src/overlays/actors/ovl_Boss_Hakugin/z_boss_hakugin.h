#ifndef Z_BOSS_HAKUGIN_H
#define Z_BOSS_HAKUGIN_H

#include "global.h"
#include "objects/object_boss_hakugin/object_boss_hakugin.h"

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
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ Vec3s unk_0E;
    /* 0x14 */ ColliderTris unk_14;
    /* 0x34 */ ColliderTrisElement unk_34;
} BossHakuginUnkStruct_2618; // size = 0x90

typedef struct BossHakuginFhgFlashUnkStruct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
} BossHakuginFhgFlashUnkStruct; // size = 0x14

typedef struct BossHakugin {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ BossHakuginActionFunc actionFunc;
    /* 0x018C */ char unk_018C[0x1];
    /* 0x018D */ s8 unk_018D;
    /* 0x018E */ s8 unk_018E;
    /* 0x018F */ s8 unk_018F;
    /* 0x0190 */ u8 unk_0190; // boolean?
    /* 0x0191 */ u8 unk_0191;
    /* 0x0192 */ u8 unk_0192;
    /* 0x0193 */ u8 unk_0193;
    /* 0x0194 */ u8 unk_0194;
    /* 0x0194 */ u8 unk_0195;
    /* 0x0196 */ u8 unk_0196;
    /* 0x0197 */ char unk_0197[0x1];
    /* 0x0198 */ s16 unk_0198;
    /* 0x019A */ s16 unk_019A;
    /* 0x019C */ s16 unk_019C;
    /* 0x019E */ s16 unk_019E;
    /* 0x01A0 */ s16 unk_01A0;
    /* 0x01A2 */ s16 unk_01A2;
    /* 0x01A4 */ s16 unk_01A4;
    /* 0x01A6 */ s16 unk_01A6;
    /* 0x01A8 */ char unk_01A8[2];
    /* 0x01AA */ s16 unk_01AA;
    /* 0x01AC */ s16 unk_01AC;
    /* 0x01AE */ s16 unk_01AE;
    /* 0x01B0 */ u32 unk_01B0;
    /* 0x01B4 */ s32 unk_01B4;
    /* 0x01B8 */ f32 unk_01B8;
    /* 0x01BC */ f32 unk_01BC;
    /* 0x01C0 */ f32 unk_01C0;
    /* 0x01C4 */ f32 unk_01C4;
    /* 0x01C8 */ f32 unk_01C8;
    /* 0x01CC */ f32 unk_01CC;
    /* 0x01D0 */ f32 unk_01D0;
    /* 0x01D4 */ f32 unk_01D4;
    /* 0x01D8 */ char unk_01D8[0x4];
    /* 0x01DC */ f32 unk_01DC;
    /* 0x01E0 */ f32 unk_01E0;
    /* 0x01E4 */ f32 unk_01E4;
    /* 0x01E8 */ Vec3s jointTable[GOHT_LIMB_MAX];
    /* 0x02AE */ Vec3s morphTable[GOHT_LIMB_MAX];
    /* 0x0374 */ Vec3s unk_0374;
    /* 0x037A */ Vec3s unk_037A;
    /* 0x0380 */ Vec3f unk_0380;
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
    /* 0x3734 */ Vec3f unk_3734[10];
    /* 0x37AC */ f32 unk_37AC;
    /* 0x37B0 */ f32 unk_37B0;
    /* 0x37B4 */ f32 unk_37B4;
    /* 0x37B8 */ ColliderSphere unk_37B8;
} BossHakugin; // size = 0x3810

#endif // Z_BOSS_HAKUGIN_H
