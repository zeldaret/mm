#ifndef Z_BOSS_05_H
#define Z_BOSS_05_H

#include "global.h"

struct Boss05;

typedef void (*Boss05ActionFunc)(struct Boss05*, PlayState*);

typedef enum {
    /* 0 */ BIO_DEKU_BABA_TYPE_0,
    /* 0 */ BIO_DEKU_BABA_TYPE_1,
    /* 0 */ BIO_DEKU_BABA_TYPE_2,
    /* 0 */ BIO_DEKU_BABA_TYPE_3,
    /* 0 */ BIO_DEKU_BABA_TYPE_4,
    /* 0 */ BIO_DEKU_BABA_TYPE_10 = 10, // Fragments?
} BioDekuBabaType;

typedef struct Boss05 {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ u8 unk15C;                          /* inferred */
    /* 0x15E */ s16 unk15E;                         /* inferred */
    /* 0x160 */ s16 unk160;                         /* inferred */
    /* 0x162 */ s16 unk162[3]; // timers
    /* 0x168 */ s16 unk168; // timer
    /* 0x16A */ s16 unk16A; // timer
    /* 0x16C */ s16 unk16C; // timer
    /* 0x170 */ Boss05ActionFunc actionFunc;
    /* 0x174 */ u8 unk174;
    /* 0x176 */ s16 unk176;
    /* 0x178 */ s16 unk178;
    /* 0x17A */ s16 unk17A; // timer
    /* 0x17C */ f32 drawDmgEffScale;
    /* 0x180 */ f32 dmgEffFrozenSteamScale;
    /* 0x184 */ f32 drawDmgEffAlpha;
    /* 0x188 */ u8 drawDmgEffState; // A bit more than just type, possibly we should name it as an internal type?
    /* 0x189 */ u8 drawDmgEffType;
    /* 0x18C */ Vec3f limbPos[1];
    /* 0x198 */ f32 unk198;
    /* 0x19C */ s16 unk19C;
    /* 0x19E */ Vec3s unk19E[7];
    /* 0x1C8 */ ColliderJntSph collider2;
    /* 0x1E8 */ ColliderJntSphElement colliderElements2[2];
    /* 0x268 */ SkelAnime skelAnime10;
    /* 0x2AC */ Vec3s jointTable10[10];
    /* 0x2E8 */ Vec3s morphTable10[10];
    /* 0x324 */ Vec3f unk324; // pos used for spawning and drawing
    /* 0x330 */ Vec3s unk330; // rotation used for spawning and drawing
    /* 0x338 */ f32 unk338;
    /* 0x33C */ Vec3f unk33C;
    /* 0x348 */ s16 unk348;
    /* 0x34C */ Vec3f unk34C;
    /* 0x35C */ f32 unk358;
    /* 0x35C */ f32 unk35C;
    /* 0x360 */ f32 unk360;
    /* 0x364 */ f32 unk364;
    /* 0x368 */ ColliderJntSph collider1;
    /* 0x388 */ ColliderJntSphElement colliderElements1[1];
    /* 0x3C8 */ SkelAnime skelAnime20;
    /* 0x40C */ Vec3s jointTable20[20];
    /* 0x484 */ Vec3s morphTable20[20];
    /* 0x4FC */ f32 lastAnimFrame;
    /* 0x500 */ Vec3s unk500;
} Boss05; // size = 0x508

#endif // Z_BOSS_05_H
