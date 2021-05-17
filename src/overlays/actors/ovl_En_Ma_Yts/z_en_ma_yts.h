#ifndef Z_EN_MA_YTS_H
#define Z_EN_MA_YTS_H

#include <global.h>

struct EnMaYts;

typedef struct EnMaYts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime unk_144;
    /* 0x188 */ char unk_188[0x4];
    /* 0x18C */ ColliderCylinder unk_18C;
    /* 0x1D8 */ s16 unk_1D8;
    /* 0x1DE */ char unk_1DE[0x2];
    /* 0x1DC */ char unk_1DC[0x24];
    /* 0x200 */ s32 unk_200;
    /* 0x204 */ Vec3s unk_204;
    /* 0x20A */ char unk_20A[0x2];
    /* 0x20C */ char unk_20C[0x88];
    /* 0x294 */ Vec3s unk_294;
    /* 0x29A */ char unk_29A[0x2];
    /* 0x29C */ char unk_29C[0x88];
    /* 0x324 */ u16 unk_324;
    /* 0x326 */ u16 unk_326;
    /* 0x328 */ u16 unk_328;
    /* 0x32A */ u16 unk_32A;
    /* 0x32C */ u16 unk_32C;
    /* 0x32E */ u16 unk_32E;
    /* 0x330 */ s16 unk_330;
    /* 0x332 */ char unk_332[0x2];
    /* 0x334 */ char unk_334[0x2];
    /* 0x336 */ u16 unk_336;
    /* 0x338 */ char unk_338[0x4];
} EnMaYts; // size = 0x33C

extern const ActorInit En_Ma_Yts_InitVars;

#endif // Z_EN_MA_YTS_H
