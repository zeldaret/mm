#ifndef Z_BOSS_05_H
#define Z_BOSS_05_H

#include "global.h"
#include "assets/objects/object_boss05/object_boss05.h"

struct Boss05;

typedef void (*Boss05ActionFunc)(struct Boss05*, PlayState*);

typedef enum BioDekuBabaType {
    /*  0 */ BIO_DEKU_BABA_LILY_PAD_WITH_HEAD,
    /*  1 */ BIO_DEKU_BABA_NO_LEAF_LILY_PAD_WITH_HEAD,
    /*  2 */ BIO_DEKU_BABA_TYPE_LILY_PAD,
    /*  3 */ BIO_DEKU_BABA_TYPE_FALLING_HEAD,
    /*  4 */ BIO_DEKU_BABA_TYPE_WALKING_HEAD,
    /* 10 */ BIO_DEKU_BABA_TYPE_FRAGMENT_BASE = 10,
    /* 10 */ BIO_DEKU_BABA_TYPE_FRAGMENT_LOWER_JAW = BIO_DEKU_BABA_TYPE_FRAGMENT_BASE,
    /* 11 */ BIO_DEKU_BABA_TYPE_FRAGMENT_UPPER_JAW,
    /* 12 */ BIO_DEKU_BABA_TYPE_FRAGMENT_BODY,
    /* 13 */ BIO_DEKU_BABA_TYPE_FRAGMENT_BACK_UPPER_LEG,
    /* 14 */ BIO_DEKU_BABA_TYPE_FRAGMENT_BACK_LOWER_LEG,
    /* 15 */ BIO_DEKU_BABA_TYPE_FRAGMENT_LEFT_UPPER_LEG,
    /* 16 */ BIO_DEKU_BABA_TYPE_FRAGMENT_LEFT_LOWER_LEG,
    /* 17 */ BIO_DEKU_BABA_TYPE_FRAGMENT_LEFT_LOWER_EYESTALK,
    /* 18 */ BIO_DEKU_BABA_TYPE_FRAGMENT_LEFT_UPPER_EYESTALK,
    /* 19 */ BIO_DEKU_BABA_TYPE_FRAGMENT_RIGHT_LOWER_EYESTALK,
    /* 20 */ BIO_DEKU_BABA_TYPE_FRAGMENT_RIGHT_UPPER_EYESTALK,
    /* 21 */ BIO_DEKU_BABA_TYPE_FRAGMENT_RIGHT_UPPER_LEG,
    /* 22 */ BIO_DEKU_BABA_TYPE_FRAGMENT_RIGHT_LOWER_LEG,
    /* 23 */ BIO_DEKU_BABA_TYPE_FRAGMENT_LEAVES
} BioDekuBabaType;

typedef struct Boss05 {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ u8 unk15C;
    /* 0x15E */ s16 unk15E;
    /* 0x160 */ s16 frameCounter;
    /* 0x162 */ s16 unk162[3]; // timers
    /* 0x168 */ s16 unk168; // timer
    /* 0x16A */ s16 damagedTimer;
    /* 0x16C */ s16 damagedFlashTimer;
    /* 0x170 */ Boss05ActionFunc actionFunc;
    /* 0x174 */ u8 unk174;
    /* 0x176 */ s16 unk176;
    /* 0x178 */ s16 unk178;
    /* 0x17A */ s16 drawDmgEffTimer;
    /* 0x17C */ f32 drawDmgEffScale;
    /* 0x180 */ f32 dmgEffFrozenSteamScale;
    /* 0x184 */ f32 drawDmgEffAlpha;
    /* 0x188 */ u8 drawDmgEffState;
    /* 0x189 */ u8 drawDmgEffType;
    /* 0x18C */ Vec3f bodyPartsPos[1];
    /* 0x198 */ f32 fallingHeadLimbScale;
    /* 0x19C */ s16 unk19C;
    /* 0x19E */ Vec3s unk19E[7];
    /* 0x1C8 */ ColliderJntSph lilyPadCollider;
    /* 0x1E8 */ ColliderJntSphElement lilyPadColliderElements[2];
    /* 0x268 */ SkelAnime lilyPadSkelAnime;
    /* 0x2AC */ Vec3s lilyPadJointTable[BIO_DEKU_BABA_LILY_PAD_LIMB_MAX];
    /* 0x2E8 */ Vec3s lilyPadMorphTable[BIO_DEKU_BABA_LILY_PAD_LIMB_MAX];
    /* 0x324 */ union {
                    Vec3f headPos;
                    Vec3f fragmentPos;
                };
    /* 0x330 */ Vec3s headRot;
    /* 0x338 */ f32 knockbackMagnitude;
    /* 0x33C */ Vec3f knockbackVelocity;
    /* 0x348 */ s16 knockbackAngle;
    /* 0x34C */ Vec3f walkTargetPos;
    /* 0x35C */ f32 walkAngularVelocityY;
    /* 0x35C */ f32 lowerJawScaleXZ;
    /* 0x360 */ f32 bodyScale;
    /* 0x364 */ f32 limbScale;
    /* 0x368 */ ColliderJntSph headCollider;
    /* 0x388 */ ColliderJntSphElement headColliderElements[1];
    /* 0x3C8 */ SkelAnime headSkelAnime;
    /* 0x40C */ Vec3s headJointTable[BIO_DEKU_BABA_HEAD_LIMB_MAX];
    /* 0x484 */ Vec3s headMorphTable[BIO_DEKU_BABA_HEAD_LIMB_MAX];
    /* 0x4FC */ f32 animEndFrame;
    /* 0x500 */ Vec3s fragmentAngularVelocity;
} Boss05; // size = 0x508

#endif // Z_BOSS_05_H
