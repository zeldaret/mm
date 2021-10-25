#ifndef Z_EN_AZ_H
#define Z_EN_AZ_H

#include "global.h"

struct EnAz;

typedef void (*EnAzActionFunc)(struct EnAz*, GlobalContext*);

typedef struct EnAz {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnAzActionFunc actionFunc;
    /* 0x0148 */ SkelAnime skelAnime;
    /* 0x018C */ ColliderCylinder collider;
    /* 0x01D8 */ Vec3s jointTable[24];
    /* 0x0268 */ Vec3s morphTable[24];
    s16 unk_2F8;
    s16 unk_2FA; // cutscene state?
    s32 animIndex;
    EnDno_ActorUnkStruct unk_300;
    f32 unk_36C;
    char unk370[4];
    u16 unk_374; // flags of some sort
    u16 unk_376; // flags of some sort
    u8 unk_378; // cutscene state?
    s16 unk_37A;
    s16 unk_37C;
    s16 unk_37E;
    s16 unk_380;
    s16 unk_382;
    s16 unk_384;
    struct EnAz* brother;
    char unk38C[0x10];
    s16 unk_39C;
    s16 unk_39E; // some sort of rotation
    char unk3A0[4];
    f32 unk_3A4;
    Vec3f unk_3A8;
    Vec3f unk_3B4; // translation 
    s16 unk_3C0; // seems to do nothing
    s16 unk_3C2;
    s16 unk_3C4;
    char unk3C6[6];
    s32 unk_3CC;
    s16 unk_3D0;
    u16 unk_3D2;
    s16 unk_3D4;
    s16 unk_3D6;
} EnAz; // size = 0x3D8

extern const ActorInit En_Az_InitVars;

#endif // Z_EN_AZ_H
