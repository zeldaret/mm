#ifndef Z_EN_MA_YTS_H
#define Z_EN_MA_YTS_H

#include <global.h>

struct EnMaYts;

typedef void (*EnMaYtsActionFunc)(struct EnMaYts*, GlobalContext*);

#define EN_MA_YTS_LIMB_COUNT 23

typedef struct EnMaYts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnMaYtsActionFunc actionFunc;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ s16 unk_1D8;
    /* 0x1DE */ char unk_1DE[0x2];
    /* 0x1DC */ char unk_1DC[0x4];
    /* 0x1E0 */ Vec3s unk_1E0;
    /* 0x1E6 */ Vec3s unk_1E6;
    /* 0x1EC */ char unk_1EC[0x4];
    /* 0x1F0 */ Vec3f unk_1F0;
    /* 0x1FC */ char unk_1FC[0x4];
    /* 0x200 */ s32 unk_200;
    /* 0x204 */ Vec3s unk_204;
    /* 0x20A */ char unk_20A[0x2];
    /* 0x20C */ char unk_20C[0x88];
    /* 0x294 */ Vec3s unk_294;
    /* 0x29A */ char unk_29A[0x2];
    /* 0x29C */ char unk_29C[0x88];
    /* 0x324 */ u16 unk_324;
    /* 0x326 */ s16 blinkTimer;
    /* 0x328 */ s16 unk_328; // blink something.
    /* 0x32A */ s16 eyeTexIndex;
    /* 0x32C */ s16 unk_32C;
    /* 0x32E */ s16 mouthTexIndex; // mouthTexIndex
    /* 0x330 */ s16 type;
    /* 0x332 */ char unk_332[0x2];
    /* 0x334 */ s16 unk_334;
    /* 0x336 */ s16 unk_336;
    /* 0x338 */ u16 textId; // messageTextId
    /* 0x33A */ char unk_33A[0x2];
} EnMaYts; // size = 0x33C

extern const ActorInit En_Ma_Yts_InitVars;

#endif // Z_EN_MA_YTS_H
