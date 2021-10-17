#ifndef Z_EN_DNQ_H
#define Z_EN_DNQ_H

#include "global.h"

struct EnDnq;

typedef void (*EnDnqActionFunc)(struct EnDnq*, GlobalContext*);
typedef void (*EnDnqFunc)(GlobalContext*, struct EnDnq*);

typedef struct EnDnq {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnDnqFunc unk_144;
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ EnDnqActionFunc actionFunc;
    /* 0x190 */ ColliderCylinder collider;
    /* 0x1DC */ u8 unk_1DC;
    /* 0x1E0 */ s32 unk_1E0;
    /* 0x1E4 */ Vec3s jointTable[33];
    /* 0x2AA */ Vec3s morphTable[33];
    /* 0x370 */ Vec3f unk_370;
    /* 0x37C */ u16 unk_37C;
    /* 0x37E */ s16 unk_37E;
    /* 0x380 */ s32* unk_380;
    /* 0x384 */ s16 unk_384;
    /* 0x386 */ s16 unk_386;
    /* 0x388 */ s16 unk_388;
    /* 0x38A */ s16 unk_38A;
    /* 0x38C */ s16 unk_38C;
    /* 0x390 */ f32 unk_390;
    /* 0x394 */ f32 unk_394;
    /* 0x398 */ s32 unk_398;
    /* 0x39C */ s32 unk_39C;
    /* 0x3A0 */ UNK_TYPE1 unk_3A0[0x4];
    /* 0x3A4 */ s32 unk_3A4;
} EnDnq; // size = 0x3A8

extern const ActorInit En_Dnq_InitVars;

#endif // Z_EN_DNQ_H
