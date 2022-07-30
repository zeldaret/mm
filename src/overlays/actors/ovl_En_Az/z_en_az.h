#ifndef Z_EN_AZ_H
#define Z_EN_AZ_H

#include "global.h"

struct EnAz;

typedef void (*EnAzActionFunc)(struct EnAz*, PlayState*);

typedef struct EnAz {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnAzActionFunc actionFunc;
    /* 0x0148 */ SkelAnime skelAnime;
    /* 0x018C */ ColliderCylinder collider;
    /* 0x01D8 */ Vec3s jointTable[24];
    /* 0x0268 */ Vec3s morphTable[24];
    /* 0x02F8 */ s16 unk_2F8;
    /* 0x02FA */ s16 unk_2FA; // cutscene state?
    /* 0x02FC */ s32 animIndex;
    /* 0x0300 */ ActorPathing unk_300;
    /* 0x036C */ f32 unk_36C;
    /* 0x0370 */ char unk370[4];
    /* 0x0374 */ u16 unk_374; // flags of some sort
    /* 0x0376 */ u16 unk_376; // flags of some sort
    /* 0x0378 */ u8 unk_378; // cutscene state?
    /* 0x037A */ s16 unk_37A;
    /* 0x037C */ s16 unk_37C;
    /* 0x037E */ s16 unk_37E;
    /* 0x0380 */ s16 unk_380;
    /* 0x0382 */ s16 unk_382;
    /* 0x0384 */ s16 unk_384;
    /* 0x0388 */ struct EnAz* brother;
    /* 0x038C */ char unk38C[0x10];
    /* 0x039C */ s16 unk_39C;
    /* 0x039E */ s16 unk_39E; // some sort of rotation
    /* 0x03A0 */ char unk3A0[4];
    /* 0x03A4 */ f32 unk_3A4;
    /* 0x03A8 */ Vec3f unk_3A8;
    /* 0x03B4 */ Vec3f unk_3B4; // translation 
    /* 0x03C0 */ s16 unk_3C0; // seems to do nothing
    /* 0x03C2 */ s16 unk_3C2;
    /* 0x03C4 */ s16 unk_3C4;
    /* 0x03C6 */ char unk3C6[6];
    /* 0x03CC */ s32 unk_3CC;
    /* 0x03D0 */ s16 unk_3D0;
    /* 0x03D2 */ u16 unk_3D2;
    /* 0x03D4 */ s16 unk_3D4;
    /* 0x03D6 */ s16 unk_3D6;
} EnAz; // size = 0x3D8

extern const ActorInit En_Az_InitVars;

#endif // Z_EN_AZ_H
