#ifndef Z_EN_YB_H
#define Z_EN_YB_H

#include <global.h>

struct EnYb;

typedef void (*EnYbActionFunc)(struct EnYb*, GlobalContext*);

#define ENYB_LIMBCOUNT 0x16

typedef struct EnYb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s limbDrawTbl[ENYB_LIMBCOUNT];
    /* 0x2A0 */ Vec3s transitionDrawTable[ENYB_LIMBCOUNT];
    ///* 0x324 */ char unk324[0x94];
    /* 0x324 */ char unk324[0x94];
    /* 0x324 */ char unk324_2[0x94]; // the fuck?
    /* 0x3B8 */ ColliderCylinder collider;
    /* 0x404 */ char unk404[0xC];
    /* 0x410 */ u16 unk410;
    /* 0x412 */ s16 unk412;
    /* 0x414 */ s16 unk414;
    /* 0x416 */ s16 unk416;
    /* 0x418 */ s16 unk418;
    /* 0x41A */ s16 unk41A[3];
    /* 0x420 */ EnYbActionFunc actionFunc;
} EnYb; // size = 0x424

extern const ActorInit En_Yb_InitVars;

#endif // Z_EN_YB_H
