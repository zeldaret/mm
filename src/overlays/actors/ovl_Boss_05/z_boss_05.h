#ifndef Z_BOSS_05_H
#define Z_BOSS_05_H

#include "global.h"

struct Boss05;

typedef void (*Boss05ActionFunc)(struct Boss05*, PlayState*);

// typedef struct Boss05 {
//     /* 0x000 */ DynaPolyActor dyna;
//     /* 0x15C */ char unk_15C[0x14];
//     /* 0x170 */ Boss05ActionFunc actionFunc;
//     /* 0x174 */ char unk_174[0x394];
// } Boss05; // size = 0x508

typedef struct Boss05 {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ u8 unk15C;                          /* inferred */
    /* 0x15D */ char pad15D[3];                     /* maybe part of unk15C[4]? */
    /* 0x160 */ s16 unk160;                         /* inferred */
    /* 0x162 */ s16 unk162[3];
    /* 0x168 */ s16 unk168;                         /* inferred */
    /* 0x16A */ s16 unk16A; /* inferred */
    /* 0x16C */ s16 unk16C; /* inferred */
    /* 0x16E */ char pad16E[2];
    /* 0x170 */ Boss05ActionFunc actionFunc;
    /* 0x174 */ char pad174[2]; // possibly this is a Vec3s
    /* 0x176 */ s16 unk176;
    /* 0x178 */ s16 unk178;
    /* 0x17A */ s16 unk17A;       /* inferred */
    /* 0x17C */ f32 unk17C;       /* inferred */
    /* 0x180 */ f32 unk180;       /* inferred */
    /* 0x184 */ f32 unk184;       /* inferred */
    /* 0x188 */ u8 unk188;        /* inferred */
    /* 0x189 */ u8 unk189;        /* inferred */
    /* 0x18A */ char pad18A[2]; /* maybe part of unk189[3]? */
    /* 0x18C */ Vec3f unk18C;
    /* 0x198 */ f32 unk198;
    /* 0x19C */ s16 unk19C;
    /* 0x19E */ Vec3s unk19E[1];
    // /* 0x1A0 */ s16 unk1A0;
    // /* 0x1A2 */ s16 unk1A2;
    /* 0x1A4 */ char pad1A4[0x24]; // Some number of other Vec3s in here
    /* 0x1C8 */ ColliderJntSph unk1C8;              /* inferred */
    /* 0x1E8 */ ColliderJntSphElement unk1E8[2];
    /* 0x268 */ SkelAnime unk268;
    /* 0x2AC */ Vec3s unk2AC[10];
    /* 0x2E8 */ Vec3s unk2E8[10];
    /* 0x324 */ Vec3f unk324;
    /* 0x330 */ Vec3s unk330; // ?
    /* 0x330 */ char unk336[0x2];
    /* 0x330 */ f32 unk338;
    /* 0x33C */ Vec3f unk33C;
    /* 0x348 */ s16 unk348;
    /* 0x34A */ char unk34A[0x2];
    /* 0x34C */ f32 unk34C;
    /* 0x350 */ char unk350[0x4];
    /* 0x35C */ f32 unk354;
    /* 0x35C */ f32 unk358;
    /* 0x35C */ f32 unk35C;
    /* 0x360 */ f32 unk360;
    /* 0x364 */ f32 unk364;
    /* 0x368 */ ColliderJntSph unk368;
    /* 0x388 */ ColliderJntSphElement unk388[1];
    /* 0x3C8 */ SkelAnime unk3C8;
    /* 0x40C */ Vec3s unk40C[20];
    /* 0x484 */ Vec3s unk484[20];
    /* 0x4FC */ f32 unk4FC;                         /* inferred */
    /* 0x500 */ s16 unk500;                         /* inferred */
    /* 0x502 */ s16 unk502;                         /* inferred */
    /* 0x504 */ char pad504[4];                     /* maybe part of unk502[3]? */
} Boss05; // size = 0x508


extern const ActorInit Boss_05_InitVars;

#endif // Z_BOSS_05_H
